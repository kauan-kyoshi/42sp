**Level 3 — Análise detalhada (Português)**

- **Binário:** `binary/level3` (ELF 64-bit, PIE, dinamicamente ligado)
- **Objetivo:** recuperar a chave usada pelo programa e reproduzir a verificação em C para justificar o raciocínio.

**1) Inspeção estática (strings / .rodata)**
- Usei `strings` e `objdump -s -j .rodata` para extrair literais. Encontrei trechos importantes:
  - O texto `Please enter key:` e `Good job.` — confirma a rotina de entrada e mensagem de sucesso.
  - A string alvo de comparação aparece como `"********"` (8 asterisks) na seção `.rodata`.
  - O formato `"%23s"` (presente na string de `.rodata`) indica que o `scanf` lê até 23 caracteres.

**2) Disassembly e lógica observada (trecho de `main`)**
- Desmontei `main` com `objdump -d -M intel` e observei a sequência lógica:
  1. Imprime o prompt e chama `scanf("%23s", buffer)`.
  2. Verifica condições sobre o buffer: existem checagens rápidas ao início do input — especificamente os dois primeiros bytes são comparados com os caracteres `'4'` e `'2'`.
  3. O programa inicializa um buffer de saída e um índice que começa em 2 (ou seja, ele começa a parsear a partir do terceiro caractere da entrada).
  4. Em um laço: pega 3 bytes consecutivos da entrada, junta em uma string temporária (ex.: "042"), chama `atoi` nessa string e escreve o resultado (um byte) no buffer de saída. Avança a posição de leitura em +3 e o índice de escrita em +1.
  5. Após consumir os grupos de 3 dígitos, termina o buffer de saída com `\0` e chama `strcmp(out, "********")`.
  6. Se `strcmp` retorna 0, chama a rotina de `ok` (imprime `Good job.`); caso contrário imprime `Nope.`.

**3) Interpretação e reconstrução do algoritmo**
- Resumo do algoritmo em palavras:
  - Entrada esperada: 23 caracteres.
  - Os dois primeiros caracteres são verificados para serem `4` e `2`.
  - Os 21 caracteres restantes são interpretados como sete grupos de 3 caracteres cada; cada grupo representa um código ASCII decimal (com 3 dígitos) que, após `atoi`, fornece o byte correspondente para preencher a string alvo.
  - Essa string montada deve ser igual a `"********"` (8 bytes com valor ASCII 42).

**4) Cálculo direto da chave**
- Queremos que cada caractere do buffer montado seja `'*'` (ASCII 42). O código ASCII decimal para `'*'` é `42`, que com 3 dígitos fica `042`.
- Portanto os sete grupos devem ser `042` cada um. A entrada completa deve ser: prefixo `"42"` + `042` * 7 = `42` + `042042042042042042042`.
- Juntando: `42042042042042042042042` — comprimento: 2 + 7*3 = 23 caracteres, compatível com `"%23s"`.

**5) Validação prática**
- Executei a verificação diretamente contra o binário original:
```bash
echo -n "42042042042042042042042\n" | ./binary/level3
```
Resultado: `Please enter key: Good job.` — confirma que a entrada recuperada é correta.

Também reconstrui o algoritmo em `level3/source.c`, compilei e validei:
```bash
gcc -O2 -std=c11 -Wall -Wextra -o level3/source level3/source.c
echo -n "42042042042042042042042\n" | ./level3/source
```
Resultado: `Please enter key: Good job.` — comporta-se igual ao binário original.

**6) Artefatos e evidências geradas**
- Arquivos adicionados em `level3/`:
  - `password` — contém `42042042042042042042042` (senha recuperada).
  - `source.c` — implementação reconstruída em C que reproduz a lógica.
  - `source` — binário compilado a partir de `source.c` (para conveniência).
  - `analysis.md` — este relatório (atualizado).
- Evidências salvas em `level3/tools/`:
  - `level3_ltrace.txt` — saída curta do `ltrace` (execução de teste).
  - `level3_ltrace_full.txt` — captura completa do `ltrace` durante execuções exploratórias.
  - `level3_rodata.txt` — dump da seção `.rodata` (mostra `"********"` e `"%23s"`).
  - `level3_test_pass.txt` — saída do binário original mostrando `Good job.` com a entrada correta.
  - `level3_source_test.txt` — saída do programa reconstruído (confirma reprodução).

**7) Observações técnicas e recomendações**
- O binário é PIE (endereços relocáveis) e 64-bit; para depuração com gdb em batch pode ser necessário desabilitar ASLR (`echo 0 | sudo tee /proc/sys/kernel/randomize_va_space`) ou usar tracing (ltrace/strace) para capturar chamadas de biblioteca (menos sensível a relocação).
- A técnica aplicada aqui combinou inspeção estática (strings/rodata + objdump) com execução observável (`ltrace`) para confirmar argumentos passados para `scanf`, `atoi` e `strcmp`.

Se quiser, eu:
- Compacto `level3/` (com `tools/` incluído) pronto para envio.
- Insiro trechos das saídas (ex.: trecho de `objdump` ou `ltrace`) dentro deste `analysis.md` para reforçar a evidência.

---

Arquivo `level3/password` contém apenas a senha: `42042042042042042042042`.
