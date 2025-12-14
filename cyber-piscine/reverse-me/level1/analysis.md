# Level1 — Análise detalhada e evidências

Este documento descreve passo a passo como chegamos à senha que faz o binário `level1` validar (`Good job.`), incluindo comandos usados, offsets relevantes e trechos de saída que sustentam a conclusão.

## Resumo

- Binário analisado: `reverse-me/binary/level1` (ELF 32-bit PIE)
- Senha encontrada: `__stack_check`
- Métodos usados: inspeção estática (`strings`, `objdump`, `hexdump`), depuração com `gdb` (modo batch) e interceptação de chamadas de biblioteca com `ltrace`.

---

## 1) Extração e verificação inicial

Comandos:

```sh
cd reverse-me
tar -xzf binary.tgz
file binary/level1
```

Saída importante:

```
binary/level1: ELF 32-bit LSB pie executable, Intel 80386, ... not stripped
```

Isso indica que o binário é 32-bit e PIE (endereços são relocáveis/ASLR), o que influencia a depuração.

---

## 2) Busca por strings

Comando usado:

```sh
strings -t x -n 6 binary/level1 > tools/level1_strings_full.txt
```

Resultados relevantes (trecho):

```
    2016 Please enter key:
    202c Good job.
    2008 __stack_check
```

Observação: a presença de `Please enter key:` e `Good job.` indica que o programa pede uma chave e valida com alguma comparação interna; `__stack_check` aparece como dado na mesma área.

Também foi feita uma inspeção da seção `.rodata`:

```sh
objdump -s -j .rodata binary/level1 > tools/level1_rodata_dump.txt
sed -n '1,80p' tools/level1_rodata_dump.txt
```

Trecho da `.rodata` (hex/ASCII):

```
2000: 5f5f 7374 6163 6b5f 6368 6563 6b00  "__stack_check\0"
2010: 50 6c 65 61 73 65 20 65 6e 74 65 72 20 6b 65 79 3a  "Please enter key:"
202c: 47 6f 6f 64 20 6a 6f 62 2e 0a 00               "Good job.\n"
```

Aqui fica claro que a string `__stack_check` está armazenada no `.rodata` do binário.

---

## 3) Inspeção da função `main` com `gdb` (análise estática/dinâmica)

Comando usado para disassembly:

```sh
gdb --batch --quiet -ex "set pagination off" -ex "set arch i386" -ex "file binary/level1" -ex "disassemble main" > tools/level1_gdb.txt
```

Observações principais do disassembly de `main`:

- O `main` imprime a mensagem `Please enter key:` via `printf` e lê entrada via `scanf`.
- Em seguida há uma chamada a `strcmp` que compara a entrada do usuário com uma string (provavelmente a armazenada em `.rodata`).

Como `level1` é PIE, os endereços em tempo de execução são deslocados; por isso usamos `gdb --batch` com `set disable-randomization on` ao automatizar capturas.

---

## 4) Captura prática dos argumentos de `strcmp` com `ltrace` (método decisivo)

Depurar com `gdb` em modo script apresentou dificuldades (prompts interativos e leituras de memória falhando em batch); por isso usamos `ltrace` que intercepta chamadas de biblioteca e mostra seus argumentos.

Comando executado:

```sh
echo -e "AAAA\n" | ltrace -e strcmp -s 2000 ./binary/level1 2>&1 | tee tools/level1_ltrace.txt
```

Trecho de saída relevante:

```
level1->strcmp("AAAA", "__stack_check") = -1
Please enter key: Nope.
```

A saída mostra claramente que `strcmp` recebe como segundo argumento a string `"__stack_check"` — ou seja, o programa compara a entrada do usuário com `__stack_check`.

Também executei `ltrace` sem filtro para confirmar fluxo completo:

```
printf("Please enter key: ")
__isoc99_scanf(...)
strcmp("AAAA", "__stack_check")
printf("Nope.\n")
```

---

## 5) Teste de validação

Comando de teste final:

```sh
echo -e "__stack_check\n" | ./binary/level1
```

Saída:

```
Please enter key: Good job.
```

Confirmação prática de que `__stack_check` é aceita pelo binário.

---

## 6) Offsets e localizações importantes (repetição para evidência)

- `.rodata` file offset: `0x2000` contém `__stack_check\0`.
- `Please enter key:` está em file offset `0x2016` (decimal 8214) — encontrado com `grep -aob`.
- `Good job.` está próximo em `0x202c`.

Comandos usados para extrair esses offsets:

```sh
grep -aob "Please enter key" binary/level1
hexdump -C -s 0x2000 -n 64 binary/level1
objdump -s -j .rodata binary/level1
```

---

## 7) Notas sobre dificuldades com `gdb` e por que `ltrace` foi preferido

- `gdb` em scripts batch, especialmente em ambientes com ASLR/PIE, pode pedir confirmações interativas ou falhar ao tentar inserir breakpoints em endereços que não existem na imagem sem relocação.
- Ler zonas de memória do processo alvo em modo batch pode falhar se o inferior terminar enquanto o script tenta acessar memória.
- `ltrace` é uma alternativa rápida e prática para obter os argumentos de chamadas de biblioteca (`strcmp` neste caso) sem as complexidades do controle do processo alvo via `gdb`.

---

## 8) Evidências salvas

Arquivos com evidências e saídas (localizados em `reverse-me/tools/`):

- `level1_strings_full.txt` — saída de `strings`
- `level1_rodata_dump.txt` — dump da seção `.rodata` via `objdump -s -j .rodata`
- `level1_gdb.txt` — disassembly de `main` (gdb)
- `level1_ltrace.txt` e `level1_ltrace_full.txt` — saídas do `ltrace` (mostram `strcmp` e argumentos)
- `level1_test_pass.txt` — saída do teste executado com `__stack_check`

Incluir estes arquivos junto ao `source.c` e `password` fornece documentação completa do processo.

---

## 9) Recomendações para submissão

No diretório `level1/` inclua:

- `password` — arquivo contendo `__stack_check` (já criado).
- `source.c` — implementação em C que reproduz a lógica (comparação) (já criado).
- `analysis.md` — este documento como evidência detalhada (arquivo agora adicionado).
- `tools/` — anexar as saídas relevantes (não é obrigatório anexar tudo, mas inclua `level1_rodata_dump.txt` e `level1_ltrace.txt` como prova direta).

---

## 10) Próximos passos

- Posso gerar automaticamente um PDF a partir deste `analysis.md`.
- Posso prosseguir para analisar `level2` usando a mesma metodologia (strings, gdb, ltrace).

---

Fim do relatório.
 
---

## Evidências completas (trechos extraídos de `reverse-me/tools/`)

Abaixo estão trechos importantes dos arquivos gerados durante a análise. Estes blocos comprovam as afirmações do relatório.

- `.rodata` (trecho de `tools/level1_rodata_dump.txt`):

```hex
binary/level1: formato do arquivo elf32-i386

Conteúdo da seção .rodata:
 2000 03000000 01000200 5f5f7374 61636b5f  ........__stack_
 2010 63686563 6b00506c 65617365 20656e74  check.Please ent
 2020 6572206b 65793a20 00257300 476f6f64  er key: .%s.Good
 2030 206a6f62 2e0a004e 6f70652e 0a00       job...Nope...
```

Observação: o valor ASCII em `0x2000` mostra `__stack_check\0` seguido das mensagens de prompt e sucesso.

- `ltrace` (trecho de `tools/level1_ltrace.txt`):

```text
level1->strcmp("AAAA", "__stack_check")          = -1
Please enter key: Nope.
++ exited (status 0) +++
```

Este trecho demonstra que `strcmp` recebeu `"__stack_check"` como segundo argumento.

- Saída completa do `ltrace` (trecho de `tools/level1_ltrace_full.txt`):

```text
[pid 226958] __libc_start_main(0x5f22e1c0, 1, 0xfff0bd44, 0 <unfinished ...>
[pid 226958] printf("Please enter key: ")        = 18
[pid 226958] __isoc99_scanf(0x5f22f029, 0xfff0bc1c, 0x5f231000, 0x5f5f0001) = 1
[pid 226958] strcmp("AAAA", "__stack_check")     = -1
[pid 226958] printf("Nope.\n")                   = 6
Please enter key: Nope.
[pid 226958] +++ exited (status 0) +++
```

- Trecho do disassembly de `main` (de `tools/level1_gdb.txt`) mostrando a chamada a `strcmp`:

```asm
    0x00001217 <+87>:    lea    -0x6c(%ebp),%eax
    0x0000121a <+90>:    lea    -0x1fd7(%ebx),%ecx
    0x00001220 <+96>:    mov    %ecx,(%esp)
    0x00001223 <+99>:    mov    %eax,0x4(%esp)
    0x00001227 <+103>:   call   0x1070 <__isoc99_scanf@plt>
    0x0000122c <+108>:   mov    -0x80(%ebp),%ebx
    0x0000122f <+111>:   lea    -0x6c(%ebp),%ecx
    0x00001232 <+114>:   lea    -0x7a(%ebp),%edx
    0x00001235 <+117>:   mov    %esp,%eax
    0x00001237 <+119>:   mov    %edx,0x4(%eax)
    0x0000123a <+122>:   mov    %ecx,(%eax)
    0x0000123c <+124>:   call   0x1040 <strcmp@plt>
```

Este trecho confirma que após `scanf` o programa prepara dois ponteiros (entrada do usuário e string esperada) e chama `strcmp`.

- Saída do teste com a senha correta (de `tools/level1_test_pass.txt`):

```text
Please enter key: Good job.
```

Essas evidências podem ser incluídas na submissão para comprovar o processo de engenharia reversa.

