# Enunciado: broken_GNL

Assignment name : broken_GNL
Expected files  : get_next_line.c get_next_line.h
Allowed functions : read, free, malloc
--------------------------------------------------------------------------------

Repare a função `get_next_line` no ficheiro `get_next_line.c`, cuja protótipo deve ser:

```c
char *get_next_line(int fd);
```

Pode ser necessário reparar também outras funções auxiliares.

Descrição da função `get_next_line`:

A sua função deve devolver uma linha que foi lida do descritor de ficheiro
passado como parâmetro.

Uma "linha lida" é definida como uma sucessão de 0 a n caracteres
terminando com ‘\n’ (código ASCII 0x0a) ou com o fim de ficheiro (EOF).

A linha deve ser retornada incluindo o ‘\n’ se este existir no final
da linha que foi lida.

Quando atingir o EOF, deve armazenar o buffer atual num `char *` e
retorná-lo. Se o buffer estiver vazio, deve retornar `NULL`.

Em caso de erro, retorne `NULL`.

Se não retornar `NULL`, o ponteiro retornado deve poder ser libertado com `free`.

O seu programa será compilado com a flag `-D BUFFER_SIZE=xx`, que deverá ser
utilizada como tamanho do buffer para as chamadas `read` nas suas funções.

A sua função não deve ter leaks de memória.

Quando atingir o EOF, a sua função não deverá manter qualquer memória alocada
com `malloc` exceto pela linha que foi retornada.

Chamar a função `get_next_line` num ciclo permitirá ler o texto disponível num
descritor de ficheiro linha a linha até ao fim do texto, independentemente do
tamanho do texto ou das suas linhas.

Assegure que a sua função comporta-se corretamente quando a leitura for feita
de um ficheiro, da entrada padrão, a partir de uma redireção, etc.

Não haverá qualquer outra chamada no descritor de ficheiro entre duas chamadas
consecutivas a `get_next_line`.

Finalmente, considera-se que o comportamento de `get_next_line` é indeterminado
quando é usado para ler ficheiros binários.
--------------------------------------------------------------------------------
