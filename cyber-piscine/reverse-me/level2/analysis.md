# Level2 — Análise detalhada e evidências

Este documento descreve como foi identificada a entrada que valida o binário `level2`.

## Resumo

- Binário: `reverse-me/binary/level2` (ELF 32-bit PIE)
- Entrada (senha) descoberta: `00101108097098101114101`
- Método: análise estática (`strings`, `objdump`, `gdb`) e dinâmica com `ltrace`. Em seguida reconstruímos a lógica e testamos a entrada.

## Observações da análise

- A inspeção do disassembly (`tools/level2_gdb.txt`) mostra que o programa:
  - lê uma string com `scanf` numa área local;
  - verifica tamanho mínimo (>=8);
  - inicializa o primeiro byte do buffer de saída com o valor `0x64` ('d');
  - itera sobre a entrada em passos de 3 bytes (pega bytes em -0x35, -0x34, -0x33 deslocados), chama `atoi` sobre a substring de 3 caracteres e armazena o valor convertido como um byte na string de saída;
  - por fim comparam a string construída com uma string fixa em `.rodata` (chamada a `strcmp`).

## Evidências (trechos)

- Trecho do disassembly que mostra a lógica de parsing e a chamada a `atoi` e `strcmp` (de `tools/level2_gdb.txt`):

```asm
   0x000013b7 <+231>:   call   0x10a0 <strlen@plt>
   0x000013c0 <+240>:   cmp    $0x8,%ecx
   0x000013c3 <+243>:   jae    0x13ee <main+286>
   ...
   0x00001422 <+338>:   mov    %eax,(%esp)
   0x00001425 <+341>:   call   0x10d0 <atoi@plt>
   0x0000142a <+346>:   mov    %al,%cl
   0x0000142c <+348>:   mov    -0x10(%ebp),%eax
   0x0000142f <+351>:   mov    %cl,-0x1d(%ebp,%eax,1)
   ...
   0x00001463 <+403>:   mov    %ecx,(%eax)
   0x00001465 <+405>:   call   0x1040 <strcmp@plt>
```

- `ltrace` mostrou claramente chamadas para `atoi` e a comparação final via `strcmp`. Exemplo (de `tools/level2_ltrace_try1.txt`):

```text
[pid ...] atoi(0xffef6c7f, 0, 9, 0xffef9fe8)  = 0
[pid ...] strcmp("d", "delabere")             = -1
```

Observação: para nosso input de teste (padrão) o programa construiu apenas a primeira letra (`'d'`) e comparou com a string alvo `"delabere"`.

## Como chegamos à entrada correta

1. Identificamos a string alvo (`delabere`) dentro do `.rodata` via `strings`/`objdump`.
2. Observando que o programa espera grupos de 3 dígitos que são passados a `atoi`, inferimos que cada grupo representa o código ASCII de uma letra (por exemplo `101` -> 'e').
3. A construção do string de saída inicia com `'d'` fixo e então popula restantes posições com os bytes retornados por `atoi` nas subsequentes iterações.
4. Notamos também que o loop de parsing começa em um offset que faz com que os primeiros 2 caracteres do input sejam *prefixo* (deslocamento de 2), portanto devemos prefixar a sequência de códigos com dois caracteres (o binário verifica que sejam '0').
5. Montamos a entrada concatenando os códigos ASCII com zero-padding (3 dígitos) para as letras alvo `delabere`, e adicionamos o prefixo `00` para alinhamento: `00` + `101108097098101114101` → `00101108097098101114101`.

## Teste final

Comando:

```sh
echo -n "00101108097098101114101\n" | ./binary/level2
```

Saída observada (capturada em `tools/level2_test_try2.txt`):

```
Please enter key: Good job.
```

## Arquivos gerados e salvos

- `tools/level2_ltrace_try1.txt` — saída do ltrace com tentativas iniciais
- `tools/level2_test_try2.txt` — saída do teste bem-sucedido
- `tools/level2_gdb.txt` — disassembly de `main`

## Conclusão

A entrada que valida `level2` é `00101108097098101114101`. Incluímos `source.c` que replica a lógica de parsing e comparação, e `password` contendo a string acima.
