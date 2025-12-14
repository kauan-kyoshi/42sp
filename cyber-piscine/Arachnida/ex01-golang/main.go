package main

import (
    "fmt"
    "io"
    "net/http"
    "os"
    "path/filepath"
    "strings"
    "sync"
    "golang.org/x/net/html"
)

func isImage(u string) bool {
    u = strings.ToLower(u)
    return strings.HasSuffix(u, ".jpg") || strings.HasSuffix(u, ".jpeg") || strings.HasSuffix(u, ".png") || strings.HasSuffix(u, ".gif") || strings.HasSuffix(u, ".bmp")
}

func download(url, outdir string, wg *sync.WaitGroup) {
    defer wg.Done()
    resp, err := http.Get(url)
    if err != nil { return }
    defer resp.Body.Close()
    if resp.StatusCode != 200 { return }
    base := filepath.Base(url)
    if base == "" { base = "image" }
    out := filepath.Join(outdir, base)
    f, err := os.Create(out)
    if err != nil { return }
    defer f.Close()
    io.Copy(f, resp.Body)
    fmt.Println("Saved:", out)
}

func parseImages(body io.Reader, base string) []string {
    doc, err := html.Parse(body)
    if err != nil { return nil }
    var imgs []string
    var walk func(*html.Node)
    walk = func(n *html.Node) {
        if n.Type == html.ElementNode && n.Data == "img" {
            for _, a := range n.Attr {
                if a.Key == "src" {
                    src := a.Val
                    if strings.HasPrefix(src, "http") {
                        imgs = append(imgs, src)
                    } else if strings.HasPrefix(src, "/") {
                        imgs = append(imgs, base+src)
                    }
                }
            }
        }
        for c := n.FirstChild; c != nil; c = c.NextSibling { walk(c) }
    }
    walk(doc)
    return imgs
}

func main() {
    if len(os.Args) < 2 {
        fmt.Println("Usage: spider <url>")
        return
    }
    url := os.Args[1]
    outdir := "data"
    os.MkdirAll(outdir, 0755)
    resp, err := http.Get(url)
    if err != nil { fmt.Println("fetch error", err); return }
    defer resp.Body.Close()
    imgs := parseImages(resp.Body, url)
    var wg sync.WaitGroup
    for _, img := range imgs {
        if isImage(img) {
            wg.Add(1)
            go download(img, outdir, &wg)
        }
    }
    wg.Wait()
}
package main

import (
	"flag"
	"fmt"
	"io"
	"net/http"
	"net/url"
	"os"
	"path"
	"path/filepath"
	"strings"
	"sync"
	"time"

	"golang.org/x/net/html"
)

var defaultExts = map[string]struct{}{".jpg": {}, ".jpeg": {}, ".png": {}, ".gif": {}, ".bmp": {}}

type rule struct {
	typ string // "allow" or "disallow"
	p   string
}

type robotsRules struct {
	agents     map[string][]rule
	crawlDelay *time.Duration
}

func newRobotsRules() *robotsRules {
	return &robotsRules{agents: make(map[string][]rule)}
}

func (r *robotsRules) add(agent, typ, p string) {
	r.agents[agent] = append(r.agents[agent], rule{typ: typ, p: p})
}

// match returns true if userAgent may fetch path
func (r *robotsRules) match(userAgent, p string) bool {
	ua := strings.ToLower(userAgent)
	var candidates []rule
	for ag, rules := range r.agents {
		if ag == "*" {
			candidates = append(candidates, rules...)
			continue
		}
		low := strings.ToLower(ag)
		if strings.Contains(ua, low) || strings.Contains(low, ua) {
			candidates = append(candidates, rules...)
		}
	}
	var matched []rule
	for _, rr := range candidates {
		if rr.p == "" {
			continue
		}
		if strings.HasPrefix(p, rr.p) {
			matched = append(matched, rr)
		}
	}
	if len(matched) == 0 {
		return true
	}
	// choose longest path
	longest := matched[0]
	for _, m := range matched[1:] {
		if len(m.p) > len(longest.p) {
			longest = m
		}
	}
	return strings.ToLower(longest.typ) == "allow"
}

// Parse a robots.txt content into robotsRules (very simple parser)
func parseRobots(base *url.URL, body string) *robotsRules {
	r := newRobotsRules()
	var currentAgents []string
	lines := strings.Split(body, "\n")
	for _, raw := range lines {
		line := raw
		if i := strings.Index(line, "#"); i >= 0 {
			line = line[:i]
		}
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}
		parts := strings.SplitN(line, ":", 2)
		if len(parts) != 2 {
			continue
		}
		field := strings.ToLower(strings.TrimSpace(parts[0]))
		value := strings.TrimSpace(parts[1])
		switch field {
		case "user-agent":
			// new group
			currentAgents = []string{value}
		case "disallow":
			agents := currentAgents
			if len(agents) == 0 {
				agents = []string{"*"}
			}
			for _, ag := range agents {
				r.add(ag, "disallow", value)
			}
		case "allow":
			agents := currentAgents
			if len(agents) == 0 {
				agents = []string{"*"}
			}
			for _, ag := range agents {
				r.add(ag, "allow", value)
			}
		case "crawl-delay":
			if v, err := time.ParseDuration(strings.TrimSpace(value) + "s"); err == nil {
				r.crawlDelay = &v
			}
		default:
		}
	}
	return r
}

func fetchRobots(client *http.Client, u *url.URL, ua string) *robotsRules {
	robotsURL := &url.URL{Scheme: u.Scheme, Host: u.Host, Path: "/robots.txt"}
	resp, err := client.Get(robotsURL.String())
	if err != nil {
		return newRobotsRules()
	}
	defer resp.Body.Close()
	if resp.StatusCode != 200 {
		return newRobotsRules()
	}
	b, err := io.ReadAll(resp.Body)
	if err != nil {
		return newRobotsRules()
	}
	return parseRobots(u, string(b))
}

type spider struct {
	start         string
	out           string
	recursive     bool
	maxDepth      int
	concurrency   int
	allowExternal bool
	delay         time.Duration
	userAgent     string

	client *http.Client

	robotsMu    sync.Mutex
	robotsCache map[string]*robotsRules

	lastMu     sync.Mutex
	lastAccess map[string]time.Time

	visitedMu sync.Mutex
	visited   map[string]struct{}

	wg     sync.WaitGroup
	sem    chan struct{}
	imgSem chan struct{}
}

func newSpider(start, out string, recursive bool, maxDepth, concurrency int, allowExternal bool, delay time.Duration, ua string) *spider {
	return &spider{
		start: start, out: out, recursive: recursive, maxDepth: maxDepth,
		concurrency: concurrency, allowExternal: allowExternal, delay: delay,
		userAgent:   ua,
		client:      &http.Client{Timeout: 20 * time.Second},
		robotsCache: make(map[string]*robotsRules),
		lastAccess:  make(map[string]time.Time),
		visited:     make(map[string]struct{}),
		sem:         make(chan struct{}, concurrency),
		imgSem:      make(chan struct{}, concurrency),
	}
}

func (s *spider) ensureDelay(u *url.URL) {
	domain := u.Host
	var effective time.Duration
	s.robotsMu.Lock()
	rr := s.robotsCache[domain]
	s.robotsMu.Unlock()
	if rr != nil && rr.crawlDelay != nil {
		if *rr.crawlDelay > s.delay {
			effective = *rr.crawlDelay
		} else {
			effective = s.delay
		}
	} else {
		effective = s.delay
	}
	if effective <= 0 {
		return
	}
	s.lastMu.Lock()
	last := s.lastAccess[domain]
	now := time.Now()
	wait := effective - now.Sub(last)
	if wait > 0 {
		s.lastMu.Unlock()
		time.Sleep(wait)
		s.lastMu.Lock()
	}
	s.lastAccess[domain] = time.Now()
	s.lastMu.Unlock()
}

func (s *spider) getRobots(u *url.URL) *robotsRules {
	domain := u.Host
	s.robotsMu.Lock()
	r, ok := s.robotsCache[domain]
	s.robotsMu.Unlock()
	if ok {
		return r
	}
	s.ensureDelay(u)
	r = fetchRobots(s.client, u, s.userAgent)
	s.robotsMu.Lock()
	s.robotsCache[domain] = r
	s.robotsMu.Unlock()
	return r
}

func (s *spider) canFetch(raw string) bool {
	u, err := url.Parse(raw)
	if err != nil {
		return false
	}
	r := s.getRobots(u)
	p := u.Path
	if p == "" {
		p = "/"
	}
	return r.match(s.userAgent, p)
}

func (s *spider) saveImage(imgURL string) {
	defer s.wg.Done()
	s.imgSem <- struct{}{}
	defer func() { <-s.imgSem }()
	if !s.canFetch(imgURL) {
		fmt.Printf("[-] robots.txt disallows image: %s\n", imgURL)
		return
	}
	u, err := url.Parse(imgURL)
	if err != nil {
		return
	}
	s.ensureDelay(u)
	req, _ := http.NewRequest("GET", imgURL, nil)
	req.Header.Set("User-Agent", s.userAgent)
	resp, err := s.client.Do(req)
	if err != nil {
		return
	}
	defer resp.Body.Close()
	if resp.StatusCode != 200 {
		return
	}
	filename := path.Base(u.Path)
	if filename == "" || filename == "/" {
		filename = "image"
	}
	os.MkdirAll(s.out, 0o755)
	dest := filepath.Join(s.out, filename)
	base := dest
	ext := filepath.Ext(dest)
	i := 1
	for {
		if _, err := os.Stat(dest); os.IsNotExist(err) {
			break
		}
		dest = fmt.Sprintf("%s_%d%s", strings.TrimSuffix(base, ext), i, ext)
		i++
	}
	f, err := os.Create(dest)
	if err != nil {
		return
	}
	defer f.Close()
	_, err = io.Copy(f, resp.Body)
	if err != nil {
		return
	}
	fmt.Printf("[+] Saved image: %s\n", dest)
}

func isImageURL(raw string) bool {
	u, err := url.Parse(raw)
	if err != nil {
		return false
	}
	ext := strings.ToLower(filepath.Ext(u.Path))
	_, ok := defaultExts[ext]
	return ok
}

func (s *spider) crawl(start string) {
	type item struct {
		u string
		d int
	}
	q := make(chan item, 1000)
	var wg sync.WaitGroup
	// start worker goroutines
	for i := 0; i < s.concurrency; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for it := range q {
				s.visitedMu.Lock()
				if _, ok := s.visited[it.u]; ok {
					s.visitedMu.Unlock()
					continue
				}
				s.visited[it.u] = struct{}{}
				s.visitedMu.Unlock()

				if it.d > s.maxDepth {
					continue
				}
				fmt.Printf("[*] Crawling (depth %d): %s\n", it.d, it.u)
				if !s.canFetch(it.u) {
					fmt.Printf("[-] robots.txt disallows crawling: %s\n", it.u)
					continue
				}
				u, err := url.Parse(it.u)
				if err != nil {
					continue
				}
				s.ensureDelay(u)
				req, _ := http.NewRequest("GET", it.u, nil)
				req.Header.Set("User-Agent", s.userAgent)
				s.sem <- struct{}{}
				resp, err := s.client.Do(req)
				<-s.sem
				if err != nil {
					continue
				}
				if resp.StatusCode != 200 {
					resp.Body.Close()
					continue
				}
				doc, err := html.Parse(resp.Body)
				resp.Body.Close()
				if err != nil {
					continue
				}
				// find img and a tags
				var f func(*html.Node)
				f = func(n *html.Node) {
					if n.Type == html.ElementNode && n.Data == "img" {
						for _, a := range n.Attr {
							if a.Key == "src" {
								imgurl := a.Val
								imgurl = resolveURL(it.u, imgurl)
								if isImageURL(imgurl) {
									s.wg.Add(1)
									go s.saveImage(imgurl)
								}
								break
							}
						}
					}
					if n.Type == html.ElementNode && n.Data == "a" && s.recursive {
						for _, a := range n.Attr {
							if a.Key == "href" {
								link := resolveURL(it.u, a.Val)
								if link == "" {
									continue
								}
								lu, err := url.Parse(link)
								if err != nil {
									continue
								}
								if lu.Scheme != "http" && lu.Scheme != "https" {
									continue
								}
								if !s.allowExternal {
									base, _ := url.Parse(s.start)
									if lu.Host != base.Host {
										continue
									}
								}
								s.visitedMu.Lock()
								_, seen := s.visited[link]
								s.visitedMu.Unlock()
								if !seen && it.d+1 <= s.maxDepth {
									q <- item{u: link, d: it.d + 1}
								}
								break
							}
						}
					}
					for c := n.FirstChild; c != nil; c = c.NextSibling {
						f(c)
					}
				}
				f(doc)
			}
		}()
	}
	// enqueue start
	q <- item{u: start, d: 0}
	// close queue when visited or when no more work: we will close after some time of inactivity
	// simple approach: wait until visited size stops growing for a short period
	go func() {
		ticker := time.NewTicker(1 * time.Second)
		defer ticker.Stop()
		var prev int
		for {
			<-ticker.C
			s.visitedMu.Lock()
			cur := len(s.visited)
			s.visitedMu.Unlock()
			if cur == prev {
				// assume done
				close(q)
				return
			}
			prev = cur
		}
	}()
	wg.Wait()
	s.wg.Wait()
}

func resolveURL(base, ref string) string {
	u, err := url.Parse(ref)
	if err == nil && u.IsAbs() {
		return u.String()
	}
	b, err := url.Parse(base)
	if err != nil {
		return ""
	}
	return b.ResolveReference(u).String()
}

func main() {
	var (
		recursive   = flag.Bool("r", false, "Recursively download images")
		maxDepth    = flag.Int("l", 5, "Maximum recursion level when -r used")
		out         = flag.String("p", "./data/", "Path to save files")
		concurrency = flag.Int("c", 10, "Max concurrent requests")
		external    = flag.Bool("e", false, "Allow following links to external domains")
		delay       = flag.Float64("d", 0.0, "Minimum delay in seconds between requests to same domain")
		ua          = flag.String("ua", "ArachnidaGoSpider/1.0", "User-Agent string to use")
	)
	flag.Parse()
	if flag.NArg() < 1 {
		fmt.Println("Uso: spider -r -l 1 -p ./data -c 1 -d 2.0 --ua 'Agent' https://example.com/")
		os.Exit(1)
	}
	start := flag.Arg(0)
	// ensure out path
	os.MkdirAll(*out, 0o755)
	sp := newSpider(start, *out, *recursive, *maxDepth, *concurrency, *external, time.Duration(*delay*float64(time.Second)), *ua)
	sp.crawl(start)
}
