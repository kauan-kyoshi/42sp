# ft_otp — One-Time Password (TOTP/HOTP) exercise

Este repositório contém apenas o projeto `ft_otp` implementado em Go. O objetivo
é gerar códigos OTP (6 dígitos) a partir de uma chave secreta hexadecimal, conforme
os requisitos do exercício (HOTP/TOTP).

Resumo rápido
- `ft_otp` permite salvar uma chave hexadecimal (64 hex chars = 32 bytes) encriptada
  em `ft_otp.key` e gerar códigos de 6 dígitos.
- O programa implementa HOTP (RFC4226) e usa um contador baseado no tempo (TOTP
  behavior): counter = unix_time / 30.

Estrutura do repositório
- `ft_otp/` : código-fonte, testes e Makefile.

Como compilar e testar (local)
1. Entre na pasta do projeto:
```bash
cd ft_otp
```
2. Compilar:
```bash
go build -o ft_otp
```
3. Gerar/armazenar chave (exemplo usando um ficheiro `key.hex` contendo 64 hex chars):
```bash
./ft_otp -g key.hex
```
4. Gerar OTP a partir do ficheiro encriptado:
```bash
./ft_otp -k ft_otp.key
```
5. Rodar os testes de comparação com `oathtool` (recomendado):
```bash
make test
```

Notas importantes
- A chave encriptada usa AES-GCM com uma passphrase estática embutida no binário.
  Para produção, substitua essa passphrase ou implemente um prompt seguro para o
  utilizador.
- O script de teste usa `oathtool` para verificar a compatibilidade. Se não tiver
  `oathtool` instalado, instale com `sudo apt install oathtool` (Linux).

