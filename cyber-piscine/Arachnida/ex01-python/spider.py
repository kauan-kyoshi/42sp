#!/usr/bin/env python3
import argparse
import asyncio
#!/usr/bin/env python3
import argparse
import asyncio
import os
import time
from urllib.parse import urljoin, urlparse
import aiohttp
import aiofiles
from bs4 import BeautifulSoup

DEFAULT_EXTENSIONS = {'.jpg', '.jpeg', '.png', '.gif', '.bmp'}


def parse_args():
    parser = argparse.ArgumentParser(description='Async spider to download images using aiohttp')
    parser.add_argument('-r', action='store_true', help='Recursively download images')
    parser.add_argument('-l', type=int, nargs='?', const=5, metavar='N',
                        help='Maximum recursion level (default 5 when -r used without N)')
    parser.add_argument('-p', metavar='PATH', default='./data/', help='Path to save files')
    parser.add_argument('-c', '--concurrency', type=int, default=10, help='Max concurrent requests (default 10)')
    parser.add_argument('-e', '--external', action='store_true', help='Allow following links to external domains')
    parser.add_argument('-d', '--delay', type=float, default=0.0, help='Minimum delay in seconds between requests to same domain')
    parser.add_argument('--user-agent', type=str, default='ArachnidaSpider/1.0', help='User-Agent string to use')
    parser.add_argument('url', help='Starting URL')
    return parser.parse_args()


class RobotsRules:
    def __init__(self):
        # mapping agent -> list of (rule_type, path)
        self.agents = {}
        self.crawl_delay = None

    def add_rule(self, agent, rule_type, path):
        self.agents.setdefault(agent, []).append((rule_type, path))

    def match(self, user_agent, path):
        # collect rules for matching agents: exact or substring match, plus '*'
        candidates = []
        ua = user_agent.lower()
        for agent, rules in self.agents.items():
            if agent == '*':
                candidates.extend(rules)
            else:
                if agent.lower() in ua or ua in agent.lower():
                    candidates.extend(rules)
        # find matching rules where path startswith rule_path
        matched = []
        for rule_type, rule_path in candidates:
            # Per robots spec: empty Disallow means allow all, treat as no-op
            if rule_path == '':
                continue
            if path.startswith(rule_path):
                matched.append((rule_type, rule_path))
        if not matched:
            return True
        # choose the rule with the longest path (priority)
        matched.sort(key=lambda x: len(x[1]), reverse=True)
        rule_type = matched[0][0]
        return rule_type.lower() == 'allow'


class AsyncSpider:
    def __init__(self, start_url, outpath, recursive=False, max_depth=5, concurrency=10, allow_external=False, delay=0.0, user_agent='ArachnidaSpider/1.0'):
        self.start_url = start_url
        self.outpath = outpath
        self.recursive = recursive
        self.max_depth = max_depth
        self.concurrency = max(1, concurrency)
        self.allow_external = allow_external
        self.allowed_exts = {e.lower() for e in DEFAULT_EXTENSIONS}
        parsed = urlparse(start_url)
        self.base_netloc = parsed.netloc
        self.visited = set()
        self.visited_lock = asyncio.Lock()
        self.session = None
        self.sem = asyncio.Semaphore(self.concurrency)
        self.queue = asyncio.Queue()
        self.queue.put_nowait((start_url, 0))
        self.image_count = 0
        self.image_lock = asyncio.Lock()
        self.robots_cache = {}  # netloc -> RobotsRules
        self.robots_lock = asyncio.Lock()
        self.delay = max(0.0, float(delay))
        self.last_access = {}  # netloc -> timestamp
        self.last_access_lock = asyncio.Lock()
        self.user_agent = user_agent

    def is_image_url(self, url):
        path = urlparse(url).path
        for ext in self.allowed_exts:
            if path.lower().endswith(ext):
                return True
        return False

    async def fetch_robots(self, url):
        parsed = urlparse(url)
        netloc = parsed.netloc
        scheme = parsed.scheme or 'http'
        async with self.robots_lock:
            if netloc in self.robots_cache:
                return self.robots_cache[netloc]
        robots_url = f"{scheme}://{netloc}/robots.txt"
        # respect per-domain politeness before fetching robots.txt
        await self.ensure_delay(robots_url)
        rules = RobotsRules()
        try:
            async with self.sem:
                async with self.session.get(robots_url, timeout=5, headers={'User-Agent': self.user_agent}) as resp:
                    if resp.status == 200:
                        text = await resp.text()
                        lines = text.splitlines()
                        current_agents = []
                        for raw in lines:
                            line = raw.split('#', 1)[0].strip()
                            if not line:
                                continue
                            if ':' not in line:
                                continue
                            field, value = line.split(':', 1)
                            field = field.strip().lower()
                            value = value.strip()
                            if field == 'user-agent':
                                current_agents = [v.strip() for v in value.split()] if value else [value]
                            elif field == 'disallow':
                                agents = current_agents or ['*']
                                for ag in agents:
                                    # keep raw path; empty value means allow all
                                    rules.add_rule(ag, 'disallow', value)
                            elif field == 'allow':
                                agents = current_agents or ['*']
                                for ag in agents:
                                    rules.add_rule(ag, 'allow', value)
                            elif field == 'crawl-delay':
                                try:
                                    rules.crawl_delay = float(value)
                                except Exception:
                                    pass
        except Exception:
            # on error assume allow all
            pass
        async with self.robots_lock:
            self.robots_cache[netloc] = rules
        return rules

    async def can_fetch(self, url):
        rules = await self.fetch_robots(url)
        parsed = urlparse(url)
        path = parsed.path or '/'
        return rules.match(self.user_agent, path)

    async def ensure_delay(self, url):
        # consider robots crawl-delay if present
        parsed = urlparse(url)
        netloc = parsed.netloc
        robots = None
        async with self.robots_lock:
            robots = self.robots_cache.get(netloc)
        if robots and robots.crawl_delay is not None:
            effective_delay = max(self.delay, robots.crawl_delay)
        else:
            effective_delay = self.delay
        if effective_delay <= 0:
            return
        now = time.time()
        async with self.last_access_lock:
            last = self.last_access.get(netloc, 0)
            wait = effective_delay - (now - last)
            if wait > 0:
                await asyncio.sleep(wait)
            self.last_access[netloc] = time.time()

    async def save_image(self, img_url):
        # check robots
        allowed = await self.can_fetch(img_url)
        if not allowed:
            print(f"[-] robots.txt disallows image: {img_url}")
            return False
        await self.ensure_delay(img_url)
        try:
            async with self.sem:
                async with self.session.get(img_url, timeout=20, headers={'User-Agent': self.user_agent}) as resp:
                    if resp.status != 200:
                        return False
                    parsed = urlparse(img_url)
                    filename = os.path.basename(parsed.path) or 'image'
                    dest_dir = os.path.abspath(self.outpath)
                    os.makedirs(dest_dir, exist_ok=True)
                    dest_path = os.path.join(dest_dir, filename)
                    base, ext = os.path.splitext(dest_path)
                    counter = 1
                    while os.path.exists(dest_path):
                        dest_path = f"{base}_{counter}{ext}"
                        counter += 1
                    f = await aiofiles.open(dest_path, 'wb')
                    async for chunk in resp.content.iter_chunked(8192):
                        await f.write(chunk)
                    await f.close()
        except Exception:
            return False
        async with self.image_lock:
            self.image_count += 1
        print(f"[+] Saved image: {dest_path}")
        return True

    async def fetch_page(self, url):
        allowed = await self.can_fetch(url)
        if not allowed:
            print(f"[-] robots.txt disallows crawling: {url}")
            return None
        await self.ensure_delay(url)
        try:
            async with self.sem:
                async with self.session.get(url, timeout=20, headers={'User-Agent': self.user_agent}) as resp:
                    if resp.status == 200:
                        text = await resp.text()
                        return text
        except Exception:
            return None
        return None

    async def worker(self):
        while True:
            try:
                url, depth = await asyncio.wait_for(self.queue.get(), timeout=1.0)
            except asyncio.TimeoutError:
                return
            async with self.visited_lock:
                if url in self.visited:
                    self.queue.task_done()
                    continue
                self.visited.add(url)
            if depth > self.max_depth:
                self.queue.task_done()
                continue
            print(f"[*] Crawling (depth {depth}): {url}")
            content = await self.fetch_page(url)
            if content:
                soup = BeautifulSoup(content, 'html.parser')
                imgs = soup.find_all('img')
                for img in imgs:
                    src = img.get('src')
                    if not src:
                        continue
                    img_url = urljoin(url, src)
                    if self.is_image_url(img_url):
                        asyncio.create_task(self.save_image(img_url))
                if self.recursive:
                    links = soup.find_all('a')
                    for a in links:
                        href = a.get('href')
                        if not href:
                            continue
                        link = urljoin(url, href)
                        parsed = urlparse(link)
                        if parsed.scheme not in ('http', 'https'):
                            continue
                        if (not self.allow_external) and parsed.netloc != self.base_netloc:
                            continue
                        async with self.visited_lock:
                            if link in self.visited:
                                continue
                        await self.queue.put((link, depth + 1))
            self.queue.task_done()

    async def run(self):
        conn = aiohttp.TCPConnector(limit_per_host=self.concurrency)
        async with aiohttp.ClientSession(connector=conn) as session:
            self.session = session
            workers = [asyncio.create_task(self.worker()) for _ in range(self.concurrency)]
            # wait for queue to be processed
            await self.queue.join()
            # cancel workers
            for w in workers:
                w.cancel()
            # allow pending image tasks to run briefly
            await asyncio.sleep(0.1)


async def main_async():
    args = parse_args()
    max_depth = 0
    if args.r:
        max_depth = args.l if args.l is not None else 5
    spider = AsyncSpider(args.url, args.p, recursive=args.r, max_depth=max_depth, concurrency=args.concurrency, allow_external=args.external, delay=args.delay, user_agent=args.user_agent)
    await spider.run()
    print(f"Done. Images saved: {spider.image_count}")


def main():
    asyncio.run(main_async())


if __name__ == '__main__':
    main()