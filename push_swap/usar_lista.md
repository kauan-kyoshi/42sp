# Inicialização de uma Lista Duplamente Ligada em C

Para iniciar essa estrutura em C, você precisa criar uma função de inicialização que aloque memória para a `t_dlist` e defina seus membros para o estado inicial de uma lista duplamente ligada vazia.

Aqui está um exemplo de como você pode estruturar a função e a lógica:

### Função de Inicialização para `t_dlist`

Você deve criar uma função que retorna um ponteiro para a nova lista (`t_dlist *`).

```c
#include <stdlib.h> // Para malloc

// As definições das suas estruturas

typedef struct s_dnode
{
    void            *data;
    struct s_dnode  *next;
    struct s_dnode  *prev;
}   t_dnode;

typedef struct s_dlist
{
    struct s_dnode  *head;
    struct s_dnode  *tail;
    unsigned long   size;
}   t_dlist;

// A função de inicialização
t_dlist *dlist_new(void)
{
    // 1. Aloca memória para a estrutura da lista.
    t_dlist *new_list = (t_dlist *)malloc(sizeof(t_dlist));

    // 2. Verifica se a alocação foi bem-sucedida.
    if (new_list == NULL)
        return (NULL);

    // 3. Inicializa os membros da lista para representar uma lista vazia.
    // Em uma lista vazia, a cabeça (head) e a cauda (tail) apontam para NULL.
    new_list->head = NULL;
    new_list->tail = NULL;
    // O tamanho é zero.
    new_list->size = 0;

    // 4. Retorna o ponteiro para a nova lista.
    return (new_list);
}
```

### Como Usar

Você pode usar essa função no seu programa principal (`main`) ou em qualquer outra função que precise de uma nova lista:

```c
#include <stdio.h>

// Inclua aqui as definições das estruturas e a função dlist_new()

int main()
{
    // Cria e inicializa a lista
    t_dlist *my_list = dlist_new();

    if (my_list == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para a lista.\n");
        return (1);
    }

    printf("Lista Duplamente Ligada inicializada com sucesso!\n");
    printf("Tamanho: %lu\n", my_list->size); // Deve imprimir 0

    // ... Adicionar lógica para inserir e remover nós ...

    // **IMPORTANTE**: Lembre-se de liberar a memória alocada no final
    // (incluindo todos os nós e a própria estrutura t_dlist).
    // Geralmente, isso é feito com uma função dlist_destroy().
    // Exemplo (simplificado, precisaria de uma função completa de limpeza):
    free(my_list);
    my_list = NULL;

    return (0);
}
```

### Por que essa estrutura?

*   **`head` e `tail`**: Apontam para `NULL` porque não há nós (elementos) na lista duplamente ligada inicialmente.
*   **`size`**: É definido como `0` para indicar que a lista está vazia.
*   **Alocação**: É feito o `malloc` para criar a estrutura `t_dlist` no heap, permitindo que ela seja acessível e persista em qualquer parte do seu programa.