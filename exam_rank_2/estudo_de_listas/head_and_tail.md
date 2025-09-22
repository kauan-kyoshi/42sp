Para ter um ponteiro para o primeiro e para o último elemento de forma eficiente, a abordagem mais comum e recomendada não é alterar a estrutura de cada nó (`t_list`), mas sim criar uma estrutura adicional que gerenciará a lista como um todo.

Esta nova estrutura conterá ponteiros para o primeiro (`head` ou `inicio`) e o último (`tail` ou `fim`) nós da sua lista. Isso oferece acesso imediato a ambas as extremidades da lista com um custo de memória mínimo (apenas dois ponteiros extras para a lista inteira).

Aqui está como você pode fazer isso:

### 1. Mantenha a Estrutura do Nó (t_list)

A sua estrutura `t_list` para cada nó da lista permanece a mesma:

```c
#ifndef FT_LIST_H
#define FT_LIST_H

#include <stdlib.h>

// Estrutura para cada nó da lista
typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;

#endif
```

### 2. Crie uma Estrutura para Gerenciar a Lista

Agora, crie uma nova estrutura que irá "conter" a sua lista. Vamos chamá-la de `t_linked_list`. É aqui que os ponteiros para o início e o fim serão armazenados.

```c
typedef struct s_linked_list
{
    t_list *head; // Ponteiro para o primeiro elemento
    t_list *tail; // Ponteiro para o último elemento
    // Opcional: você também pode adicionar um contador de tamanho
    // size_t size;
}              t_linked_list;
```

### Exemplo de Implementação e Uso

Veja como a estrutura `t_linked_list` seria usada em um código prático. O ponteiro `head` apontará para o primeiro nó, e o `tail` para o último.

```c
#include <stdio.h>
#include <stdlib.h>

// --- Definições das estruturas (como acima) ---

typedef struct s_list
{
    struct s_list *next;
    void          *data;
}              t_list;

typedef struct s_linked_list
{
    t_list *head;
    t_list *tail;
}              t_linked_list;


// --- Funções para manipular a lista ---

// Função para inicializar a lista (vazia)
void list_init(t_linked_list *list)
{
    list->head = NULL;
    list->tail = NULL;
}

// Função para adicionar um elemento no final da lista
void list_push_back(t_linked_list *list, void *data)
{
    // 1. Criar um novo nó
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return; // Falha na alocação de memória
    new_node->data = data;
    new_node->next = NULL;

    // 2. Se a lista estiver vazia
    if (list->head == NULL)
    {
        list->head = new_node; // O novo nó é o primeiro
        list->tail = new_node; // E também o último
    }
    else // 3. Se a lista já tiver elementos
    {
        list->tail->next = new_node; // O antigo último nó aponta para o novo
        list->tail = new_node;       // O novo nó se torna o último
    }
}

int main(void)
{
    t_linked_list my_list;
    list_init(&my_list);

    char *str1 = "primeiro";
    char *str2 = "segundo";
    char *str3 = "terceiro (ultimo)";

    printf("Adicionando elementos...\n");
    list_push_back(&my_list, str1);
    list_push_back(&my_list, str2);
    list_push_back(&my_list, str3);

    if (my_list.head)
        printf("Primeiro elemento: %s\n", (char *)my_list.head->data);

    if (my_list.tail)
        printf("Último elemento: %s\n", (char *)my_list.tail->data);

    // Lembre-se de liberar a memória alocada para cada nó no final
    // (código de liberação omitido por simplicidade)

    return (0);
}
```

### Vantagens desta Abordagem

*   **Eficiência:** Você pode acessar o primeiro e o último elemento em tempo constante, O(1), sem precisar percorrer a lista inteira.
*   **Inserção Rápida:** Adicionar um novo elemento no final da lista também se torna uma operação O(1).
*   **Memória:** É muito mais eficiente em termos de memória do que adicionar dois ponteiros extras a *cada* nó da lista.

Esta é a maneira padrão e mais otimizada de se trabalhar com listas encadeadas quando o acesso rápido ao início e ao fim é necessário. A alternativa seria uma **lista duplamente encadeada**, que também inclui um ponteiro para o elemento *anterior* em cada nó, permitindo a navegação em ambos os sentidos.