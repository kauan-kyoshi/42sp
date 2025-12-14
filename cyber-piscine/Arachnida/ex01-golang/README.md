# Arachnida — Spider em Go (ex01-golang)

Esta pasta contém uma implementação em Go do spider do exercício, com funcionalidade semelhante à versão em Python: busca e download de imagens, respeito básico a `robots.txt`, controle de profundidade, concorrência e politeness.

## Arquivos

- `main.go` — implementa o spider.
- `go.mod` — módulo e dependência (`golang.org/x/net` para parse HTML).

## Requisitos

- Go 1.20+ instalado.

## Compilar

No diretório `ex01-golang` execute:

```bash
go mod tidy
go build -o arachnida_spider
```

Isso cria o binário `arachnida_spider`.

## Uso

Exemplo seguro (site real — comece conservador):

```bash
./arachnida_spider -r -l 0 -c 1 -d 2.0 --ua "ArachnidaGo/0.1 (contact)" https://exemplo.com/
```

Opções principais:

- `-r` : recursivo.
- `-l N` : profundidade máxima (quando `-r` é usada).
- `-p PATH` : diretório de saída (default `./data/`).
- `-c` : concorrência máxima.
- `-e` : permitir links externos.
- `-d` : delay mínimo por domínio (segundos).
- `--ua` : user-agent.

Observações:

- O parser de `robots.txt` é uma implementação simples — atende casos comuns com `User-agent`, `Allow`, `Disallow` e `Crawl-delay`.
- Use parâmetros conservadores (`-c 1 -d 2.0`) ao testar em sites reais.

