# Enunciado: n_queens

Assignment name : n_queens

Expected files : *.c *.h

Allowed functions : atoi, fprintf, write, calloc, malloc, free, realloc, stdout, stderr

-------------------------------------------------------------------------

Escreva um programa que imprima todas as soluções do problema das n rainhas
para um `n` passado como argumento.

Não testaremos com valores negativos.
A ordem das soluções não é importante.

Você deverá exibir as soluções no seguinte formato:

<p1> <p2> <p3> ...

onde `pn` é o índice da linha da rainha em cada coluna, começando em 0.

Por exemplo, isto deverá funcionar:

```
$> ./n_queens 2 | cat -e

$> ./n_queens 4 | cat -e
1 3 0 2$
2 0 3 1$

$> ./n_queens 7 | cat -e
0 2 4 6 1 3 5$
0 3 6 2 5 1 4$
etc...
```

O seu código pode ser distribuído em vários ficheiros `.c` e `.h` conforme
necessário.

Em caso de argumentos inválidos (por exemplo nenhum argumento), pode optar por
retornar `1` e/ou escrever uma mensagem de erro em `stderr` usando `fprintf`.

--------------------------------------------------------------------------------
