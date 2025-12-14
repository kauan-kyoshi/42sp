#!/usr/bin/env python3
import asyncio
import aiohttp
import aiofiles
import argparse
import os
import time
from urllib.parse import urljoin, urldefrag, urlparse
from bs4 import BeautifulSoup

semaphore = None
visited = set()

async def fetch(session, url):
    try:
        async with session.get(url, timeout=15) as resp:
            if resp.status == 200:
                return await resp.text()
    except Exception:
        return None

async def save_image(session, url, outdir):
    try:
        async with session.get(url) as r:
            if r.status == 200 and 'image' in r.headers.get('Content-Type',''):
                fname = os.path.basename(urlparse(url).path) or 'image'
                path = os.path.join(outdir, fname)
                async with aiofiles.open(path, 'wb') as f:
                    await f.write(await r.read())
                print(f"[+] Saved image: {path}")
    except Exception as e:
        return

async def crawl(session, url, outdir, depth, max_depth, delay, sem):
    if depth > max_depth:
        return
    parsed = urldefrag(url)[0]
    if parsed in visited:
        return
    visited.add(parsed)
    await asyncio.sleep(delay)
    async with sem:
        html = await fetch(session, parsed)
    if not html:
        return
    soup = BeautifulSoup(html, 'html.parser')
    # download images
    imgs = set()
    for img in soup.find_all('img'):
        src = img.get('src')
        if not src: continue
        imgurl = urljoin(parsed, src)
        imgs.add(imgurl)
    tasks = [save_image(session, u, outdir) for u in imgs]
    await asyncio.gather(*tasks)
    # follow links
    links = set()
    for a in soup.find_all('a'):
        href = a.get('href')
        if not href: continue
        link = urljoin(parsed, href)
        if urlparse(link).scheme in ('http','https'):
            links.add(link)
    tasks = [crawl(session, l, outdir, depth+1, max_depth, delay, sem) for l in links]
    await asyncio.gather(*tasks)

async def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('start')
    parser.add_argument('-r', action='store_true', help='recursive')
    parser.add_argument('-l', type=int, default=0, help='max depth')
    parser.add_argument('-c', type=int, default=4, help='concurrency')
    parser.add_argument('-d', type=float, default=1.0, help='delay seconds')
    parser.add_argument('-p', default='data', help='output path')
    args = parser.parse_args()
    outdir = args.p
    os.makedirs(outdir, exist_ok=True)
    max_depth = args.l if args.r else 0
    sem = asyncio.Semaphore(args.c)
    async with aiohttp.ClientSession() as session:
        await crawl(session, args.start, outdir, 0, max_depth, args.d, sem)

if __name__ == '__main__':
    asyncio.run(main())
