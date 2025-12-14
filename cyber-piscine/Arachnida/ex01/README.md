# Arachnida — Spider (Python)

Versão em Python do spider (async) que baixa imagens de páginas web.

Dependências

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

Exemplo de uso

```bash
python spider.py -r -l 1 -c 3 -d 1.5 https://example.com
```

Flags principais (implementação mínima):
- `-r` : recursivo
- `-l N` : profundidade máxima
- `-c N` : concorrência
- `-d S` : politeness (segundos entre requests por domínio)

Arquivos fundamentais: `spider.py`.
