# Escorpião — analisador e editor de metadados de imagens (Go)

Projeto `Escorpião` (ex02-golang) — utilitário em Go para inspecionar, limpar e editar metadados EXIF/PNG de imagens, com uma interface web local para visualização e edição.

Funcionalidades principais
- Ler e exibir metadados básicos de arquivos de imagem (tamanho, data de modificação).
- Ler EXIF de JPEGs (data/hora, GPS, tags) usando `github.com/rwcarlsen/goexif`.
- Ler chunks textuais de PNG (`tEXt`, `iTXt`, `zTXt`).
- Limpar EXIF APP1 de JPEGs (função `--clear`) — cria backup `file.jpg.bak`.
- Restaurar backup com `--undo`.
- Edição seletiva de tags via `exiftool` (`--set-tag` / `--remove-tag`) — cria backup `.bak` antes de alterar.
- Interface web local (GUI) que lista arquivos, mostra preview e permite operações (`/api/*`).

Status: pronto para uso local. O frontend moderno está em `web/` e a API serve esse frontend quando a opção `--gui` é usada.

Requisitos
- Go toolchain (para compilar): `go` (1.20+ recomendado).
- `exiftool` (necessário somente para operações de escrita/edição; leitura básica e limpeza por `--clear` não exigem `exiftool`).
  - Debian/Ubuntu: `sudo apt install libimage-exiftool-perl`
  - macOS (Homebrew): `brew install exiftool`
- (Opcional) Navegador para acessar GUI em `http://127.0.0.1:8080/`.

Como compilar
1. Entre na pasta do projeto:
```bash
cd /home/kyoshi/42/42-sp/cyber-piscine/Arachnida/ex02-golang
```
2. Compile o binário:
```bash
go build -o escorpiao
```

Uso — CLI (modo terminal)
- Mostrar metadados no terminal:
```bash
./escorpiao imagem.jpg
```
- Remover EXIF de um JPEG (cria `imagem.jpg.bak`):
```bash
./escorpiao -clear imagem.jpg
```
- Restaurar backup (`.bak`):
```bash
./escorpiao -undo imagem.jpg
```
- Editar tags (usa `exiftool`):
```bash
./escorpiao --set-tag Artist="Meu Nome" imagem.jpg
./escorpiao --remove-tag Artist imagem.jpg
```
Você pode passar múltiplos arquivos como argumentos.

Uso — GUI (interface web local)
1. Inicie o servidor web local:
```bash
./escorpiao --gui
```
2. Abra no navegador: `http://127.0.0.1:8080/`.

Endpoints principais (API interna)
- `GET /api/files` — lista de arquivos suportados no diretório onde o servidor roda.
- `GET /api/metadata?file=<nome>` — retorna JSON com metadados (EXIF, PNG text chunks, tamanho, mod_time).
- `POST /api/clear?file=<nome>` — limpa EXIF do JPEG (usa `clearExifJPEG`, cria backup `.bak`).
- `POST /api/undo?file=<nome>` — restaura backup `file.bak`.
- `POST /api/edit` — corpo JSON {"file":"nome","remove":[],"set":[]} para editar tags via `exiftool`.

Observações sobre execução local
- O servidor atualmente lista arquivos no diretório de trabalho (`.`). Para ver suas imagens na GUI, coloque os arquivos de imagem na mesma pasta do binário ou execute o binário a partir da pasta que contém os arquivos.
- Backups: operações destrutivas criam backups com sufixo `.bak` no mesmo diretório.
- Se `exiftool` não estiver instalado, os endpoints/flags de edição retornarão erro informando a falta do utilitário.

Logs
- Ao rodar `./escorpiao --gui` o servidor escreve logs em stdout. Se preferir executar em background e coletar logs:
```bash
nohup ./escorpiao --gui > escorpiao.log 2>&1 &
tail -f escorpiao.log
```

Melhorias sugeridas (próximos passos)
- Tornar o diretório de dados configurável via variável de ambiente `DATA_DIR`.
- Tornar o endereço de bind configurável (`LISTEN_ADDR`) para permitir `0.0.0.0:8080` quando necessário.
- Adicionar autenticação / proteção da GUI se exposta em rede.
- Mover armazenamento para object storage (S3/GCS) para suportar deploy serverless.

Problemas e soluções comuns
- `/api/files` retorna `null` ou lista vazia: verifique se há arquivos suportados no diretório do binário; rode `ls -la` na pasta e coloque imagens lá.
- Erro `exiftool not found` ao chamar edição: instale `exiftool` conforme indicado acima.

Licença
- Sem licença explícita — trate como código de exercício. Me avise se quiser que eu adicione uma licença permissiva (MIT/Apache-2.0).
