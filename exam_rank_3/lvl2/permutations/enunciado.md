# Enunciado: permutations

Assignment name  : permutations
Expected files   : *.c *.h
Allowed functions: puts, malloc, calloc, realloc, free, write
---------------------------------------------------------------

Escreva um programa que imprima todas as permutações de uma string passada
como argumento.

As soluções devem ser emitidas por ordem alfabética.

Não testaremos o seu programa com strings que contenham caracteres duplicados
(por exemplo: 'abccd').

Exemplos de execução esperados:

```
$> ./permutations a | cat -e
a$

$> ./permutations ab | cat -e
ab$
ba$

$> ./permutations abc | cat -e
abc$
acb$
bac$
bca$
cab$
cba$
```

O seu código pode conter vários ficheiros `.c` e `.h` conforme necessário.

Em caso de invocação sem argumentos, com argumentos inválidos ou outros
erros de entrada, pode retornar `1` (comportamento conforme a sua escolha).

--------------------------------------------------------------------------------
