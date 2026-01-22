# Enunciado: filter

Assignment name: filter
Expected files: filter.c
Allowed functions: read, write, strlen, memmem, memmove, malloc, calloc,
realloc, free, printf, fprintf, stdout, stderr, perror
--------------------------------------------------------------------------------

Escreva um programa que receba exatamente um argumento.

O programa deverá ler da `stdin` e escrever tudo o que for lido para a `stdout`,
exceto que toda ocorrência da string `s` (o argumento) deve ser substituída por `*`
replicado tantas vezes quanto o comprimento de `s`.

O seu programa será testado com tamanhos de buffer aleatórios, usando uma função
`read` personalizada. Portanto o buffer usado nas leituras pode conter um número
variável de caracteres em cada chamada.

Exemplos:

```
./filter bonjour
```
comportará-se como:

```
sed 's/bonjour/*******/g'
```

```
./filter abc
```
comportará-se como:

```
sed 's/abc/***/g'
```

Mais genericamente o seu programa deverá equivaler ao script `filter.sh` presente
neste diretório (pode comparar o seu programa com ele).

Em caso de erro durante uma leitura (`read`) ou uma alocação (`malloc`/`realloc`/`calloc`),
deve escrever em `stderr` a string "Error: " seguida da mensagem de erro e
retornar com código `1`.

Se o programa for chamado sem argumentos, com um argumento vazio ou com múltiplos
argumentos, deve retornar `1`.

Exemplos de uso esperado:

```
$> echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc | cat -e
***defaaa***de******d***$
$> echo 'ababcabababc' | ./filter ababc | cat -e
*****ab*****$
```

NOTAS:
- Para usar `memmem` inclua:

```
#define _GNU_SOURCE
#include <string.h>
```

- Para `perror` inclua `<errno.h>`.
- Para `read` inclua `<fcntl.h>` quando necessário.

--------------------------------------------------------------------------------
