# Arachnida — Spider (ex01)

Este projeto é um spider assíncrono em Python para buscar e baixar imagens de páginas web, implementado com `asyncio` + `aiohttp` e um parser simples de `robots.txt` para respeitar regras básicas de crawling.

**Aviso importante:** use este programa com responsabilidade. Sempre respeite o `robots.txt` dos sites, as leis locais e os Termos de Serviço do site alvo. Teste em ambientes controlados (ex.: site de teste local) antes de usar em sites reais.

## Estrutura do repositório

- `spider.py` — programa principal (async, usa `aiohttp`, `aiofiles`, `bs4`).
- `create_test_site.py` — gera um diretório `test_site/` com páginas e imagens para testes locais.
- `requirements.txt` — dependências: `aiohttp`, `aiofiles`, `beautifulsoup4`.

Arquivos de saída padrão são salvos em `./data/` (pasta criada pelo `spider.py` ao salvar imagens), a menos que você especifique outra com `-p`.

## Recursos implementados

- Varredura assíncrona (concor­rência controlada via `-c`).
- Respeito básico a `robots.txt` (User-agent groups, `Allow`/`Disallow`, `Crawl-delay`).
- Filtragem por extensões de imagem comuns: `.jpg`, `.jpeg`, `.png`, `.gif`, `.bmp`.
- Opção de seguir links externos (`-e`).
- Controles: profundidade de crawl, politeness (delay por domínio), limite de concorrência.

Observação: no estado atual do código não há uma flag `--dry-run` implementada — posso implementá-la se desejar (ela listaria URLs sem baixar arquivos).

## Requisitos

- Python 3.10+ (testado em 3.12).
- Sistema com suporte a virtualenv (recomendado).

## Setup (recomendado)

1. Clone ou posicione-se no diretório do exercício (`Arachnida/ex01`).
2. Crie um ambiente virtual e ative-o:

```bash
cd /path/to/Arachnida/ex01
python3 -m venv .venv
source .venv/bin/activate
```

3. Instale as dependências:

```bash
pip install -r requirements.txt
```

Se encontrar erro `externally-managed-environment` siga a recomendação: use virtualenv (como acima) e instale as dependências dentro da venv.

## Testes locais (seguro)

Há um utilitário para gerar um site de teste estático em `test_site/`.

1. Gere o site de teste:

```bash
python3 create_test_site.py
```

2. Sirva localmente (porta 8000):

```bash
python3 -m http.server 8000 --directory test_site
```

3. Execute o spider contra o site local (modo recursivo, profundidade 1):

```bash
.venv/bin/python spider.py -r -l 1 -c 4 -d 0.2 http://localhost:8000/index.html
```

Verifique a pasta `data/` para ver imagens baixadas.

## Como executar em sites reais — passos e recomendações

1. Sempre inspecione o `robots.txt` do site alvo (ex.: `https://example.com/robots.txt`). Verifique se o caminho que pretende acessar não está bloqueado.
2. Use parâmetros conservadores para começar e reduzir impacto:
   - `-c 1` — um pedido por vez.
   - `-d 2.0` — pelo menos 2 segundos entre pedidos ao mesmo domínio.
   - `-r -l 0` — recursão ativada, mas profundidade 0 (apenas a página inicial) — útil para descobrir imagens na raiz.

Exemplo recomendado (seguro):

```bash
.venv/bin/python spider.py -r -l 0 -c 1 -d 2.0 --user-agent "SeuNomeBot/0.1 (contato: seu@email)" https://exemplo.com/
```

Se quiser vasculhar páginas internas aumente `-l` gradualmente (`1`, `2`, ...) e monitore o comportamento e a carga no site.

### Observações sobre `robots.txt` e politeness

- O spider obtém `/robots.txt` e aplica regras básicas antes de baixar páginas ou imagens.
- Se o `robots.txt` declarar `Crawl-delay`, o spider irá respeitar esse valor (ele combina com `-d` usando o maior dos dois valores).

## Flags e opções (resumo)

- `-r` : ativa crawl recursivo.
- `-l N` : profundidade máxima quando `-r` é usada (por padrão 5 quando `-r` é passado sem N no design original; no uso atual especifique explicitamente).
- `-p PATH` : diretório onde salvar arquivos (default `./data/`).
- `-c, --concurrency` : número máximo de pedidos simultâneos (default 10).
- `-e, --external` : permitir seguir links para domínios externos.
- `-d, --delay` : delay mínimo (em segundos) entre pedidos ao mesmo domínio.
- `--user-agent` : string do User-Agent usada nas requisições.

## Exemplo prático (site real, incremento seguro)

1. Comece com:

```bash
.venv/bin/python spider.py -r -l 0 -c 1 -d 2.0 --user-agent "ArachnidaTest/0.1 (contact)" https://exemplo.com/
```

2. Se os resultados estiverem OK (e `robots.txt` permitir), aumente para `-l 1`:

```bash
.venv/bin/python spider.py -r -l 1 -c 1 -d 2.0 --user-agent "ArachnidaTest/0.1 (contact)" https://exemplo.com/
```

3. Para aumentar velocidade com responsabilidade, aumente `-c` e reduza `-d` gradualmente, preferencialmente depois de conversar com o administrador do site.

## Logs e saída

- O script imprime linhas de progresso (`[*] Crawling ...`, `[-] robots.txt disallows ...`, `[+] Saved image: ...`).
- As imagens são salvas em `./data/` (ou no caminho indicado por `-p`).

## Limpeza

Para remover tudo que foi baixado:

```bash
rm -rf data/*
```

## Problemas comuns e soluções

- `ModuleNotFoundError: No module named 'aiohttp'` — crie e ative a venv e instale as dependências (veja a seção Setup).
- `Address already in use` ao rodar `http.server` — escolha outra porta `--directory test_site` ou finalize processo que ocupa a porta.



