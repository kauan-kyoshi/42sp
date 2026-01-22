# Enunciado: powerset

Assignment name  : powerset
Expected files   : *.c *.h
Allowed functions: atoi, printf, fprintf, malloc, calloc, realloc, free, stdout,
write
--------------------------------------------------------------------------------

Escreva um programa que receba como argumentos um inteiro `n` seguido de um
conjunto `s` de inteiros distintos.

O seu programa deverá imprimir todos os subconjuntos de `s` cuja soma dos
elementos seja igual a `n`.

A ordem das linhas (dos subconjuntos) não é importante, mas a ordem dos
elementos dentro de um subconjunto deve seguir a ordem do conjunto inicial
`s`. Assim não deve haver duplicados como `1 2` e `2 1`.

O subconjunto vazio é válido e deverá ser representado por uma linha vazia.

Em caso de erro de `malloc`, o programa deve terminar com o código de saída
`1`.

Não testaremos conjuntos com elementos repetidos (por exemplo `1 1 2`).

Exemplos de execução esperados:

```
$> ./powerset 3 1 0 2 4 5 3 | cat -e
3$
0 3$
1 2$
1 0 2$

$> ./powerset 12 5 2 1 8 4 3 7 11 | cat -e
8 4$
1 11$
1 4 7$
1 8 3$
2 3 7$
5 7$
5 4 3$
5 2 1 4$

$> ./powerset 0 1 -1 | cat -e
$
1 -1$

$> ./powerset 7 3 8 2 | cat -e

// Outros testes possíveis:
$> ./powerset 100 1 2 3 ... | cat -e
$> ./powerset -1 1 2 3 4 5 -10 | cat -e
$> ./powerset 0 -1 1 2 3 -2 | cat -e

```

Observações:
- Pode repartir o programa em vários ficheiros `.c` e `.h` se desejar.
- Use as funções permitidas listadas no topo.
- Em caso de argumentos inválidos o comportamento pode ser retornar `1`.

--------------------------------------------------------------------------------
