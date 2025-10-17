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















Com certeza. Para popular a lista duplamente ligada com os argumentos inteiros passados para a `main` (através de `argv`), você precisa seguir alguns passos:

1.  **Iterar sobre `argv`**: Percorrer o array de strings `argv`, começando pelo índice 1 (já que `argv[0]` é o nome do programa).
2.  **Converter String para Inteiro**: Cada argumento em `argv` é uma string. Você precisará convertê-lo para um número inteiro. A função `atoi` da biblioteca `<stdlib.h>` é uma maneira simples de fazer isso.
3.  **Criar um Novo Nó**: Para cada número, você precisará alocar memória para um novo `t_dnode`.
4.  **Alocar Memória para o Dado**: Como o campo `data` da sua estrutura é um `void *`, você precisa alocar memória dinamicamente para armazenar o valor inteiro. Isso evita que o dado seja perdido quando a variável local sair de escopo.
5.  **Adicionar o Nó à Lista**: Criar uma função, como `dlist_append()`, que adicione o novo nó no final da lista, atualizando os ponteiros `head`, `tail` e o `size`.

Abaixo está o código completo em formato `.md`, incluindo as funções necessárias e a lógica na `main`.

---

# Populando uma Lista Duplamente Ligada com Argumentos da Linha de Comando (argv)

Para popular a lista com inteiros passados como parâmetros para a função `main`, você precisa:
1.  Percorrer os argumentos da linha de comando (`argv`).
2.  Converter cada argumento (que é uma string) para um inteiro.
3.  Criar um novo nó para cada inteiro.
4.  Adicionar o nó à lista.

Vamos expandir o código anterior para incluir a criação de nós e uma função para adicioná-los ao final da lista.

### 1. Definições das Estruturas e Funções

Primeiro, mantemos as estruturas e a função `dlist_new()` e adicionamos duas novas funções:
*   `dlist_new_node()`: Para criar um novo nó.
*   `dlist_append()`: Para adicionar um nó no final da lista.

```c
#include <stdio.h>
#include <stdlib.h> // Para malloc, free e atoi

// Definição do nó
typedef struct s_dnode
{
    void            *data;
    struct s_dnode  *next;
    struct s_dnode  *prev;
}   t_dnode;

// Definição da lista
typedef struct s_dlist
{
    struct s_dnode  *head;
    struct s_dnode  *tail;
    unsigned long   size;
}   t_dlist;

/*
** Função para criar uma nova lista vazia.
*/
t_dlist *dlist_new(void)
{
    t_dlist *new_list = (t_dlist *)malloc(sizeof(t_dlist));
    if (new_list == NULL)
        return (NULL);
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;
    return (new_list);
}

/*
** Função para criar um novo nó com o dado fornecido.
** Aloca memória para o dado para que ele persista.
*/
t_dnode *dlist_new_node(void *data)
{
    t_dnode *new_node = (t_dnode *)malloc(sizeof(t_dnode));
    if (new_node == NULL)
        return (NULL);

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return (new_node);
}

/*
** Função para adicionar um nó no final da lista.
*/
void dlist_append(t_dlist *list, t_dnode *new_node)
{
    if (list == NULL || new_node == NULL)
        return;

    // Se a lista está vazia, o novo nó é tanto a cabeça quanto a cauda.
    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        // O "próximo" da cauda atual aponta para o novo nó.
        list->tail->next = new_node;
        // O "anterior" do novo nó aponta para a cauda antiga.
        new_node->prev = list->tail;
        // A nova cauda da lista é o novo nó.
        list->tail = new_node;
    }
    // Incrementa o tamanho da lista.
    list->size++;
}
```

### 2. Lógica na `main` para Popular a Lista

A função `main` receberá `argc` (a contagem de argumentos) e `argv` (o vetor de argumentos).

```c
// Função auxiliar para imprimir a lista (para verificação)
void print_list(t_dlist *list)
{
    if (list == NULL || list->head == NULL)
    {
        printf("A lista está vazia.\n");
        return;
    }

    t_dnode *current = list->head;
    printf("Conteúdo da lista (Tamanho: %lu):\n", list->size);
    while (current != NULL)
    {
        // Usamos *(int *) para converter o void* de volta para um inteiro
        printf("%d -> ", *(int *)current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Função para liberar toda a memória alocada
void dlist_destroy(t_dlist *list)
{
    if (list == NULL)
        return;
    
    t_dnode *current = list->head;
    t_dnode *next_node;

    while (current != NULL)
    {
        next_node = current->next;
        free(current->data); // Libera a memória do dado
        free(current);       // Libera o nó
        current = next_node;
    }
    free(list); // Libera a estrutura da lista
}


int main(int argc, char *argv[])
{
    // 1. Verifica se foram passados argumentos numéricos
    if (argc < 2)
    {
        fprintf(stderr, "Uso: %s <num1> <num2> ... <numN>\n", argv[0]);
        return (1);
    }

    // 2. Cria a lista
    t_dlist *my_list = dlist_new();
    if (my_list == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para a lista.\n");
        return (1);
    }

    // 3. Itera sobre argv, converte e adiciona à lista
    for (int i = 1; i < argc; i++)
    {
        // Converte a string para inteiro
        int value = atoi(argv[i]);

        // Aloca memória para armazenar o valor inteiro
        int *data_ptr = (int *)malloc(sizeof(int));
        if (data_ptr == NULL) {
            fprintf(stderr, "Erro de alocação para o dado.\n");
            dlist_destroy(my_list); // Libera o que já foi alocado
            return (1);
        }
        *data_ptr = value;

        // Cria um novo nó com o dado
        t_dnode *new_node = dlist_new_node(data_ptr);
        if (new_node == NULL)
        {
            fprintf(stderr, "Erro ao alocar memória para o nó.\n");
            free(data_ptr); // Libera o dado que não será usado
            dlist_destroy(my_list);
            return (1);
        }

        // Adiciona o nó no final da lista
        dlist_append(my_list, new_node);
    }

    printf("Lista populada com sucesso a partir dos argumentos!\n");

    // 4. Imprime a lista para verificar
    print_list(my_list);

    // 5. Libera toda a memória alocada (lista, nós e dados)
    dlist_destroy(my_list);
    printf("Memória liberada com sucesso.\n");

    return (0);
}
```

### Como Compilar e Executar

1.  Salve o código em um arquivo, por exemplo, `dlist_main.c`.
2.  Compile-o com um compilador C (como o GCC):
    ```sh
    gcc dlist_main.c -o dlist_program
    ```3.  Execute o programa passando números como argumentos:
    ```sh
    ./dlist_program 10 25 5 99 150
    ```

#### Saída Esperada:

```
Lista populada com sucesso a partir dos argumentos!
Conteúdo da lista (Tamanho: 5):
10 -> 25 -> 5 -> 99 -> 150 -> NULL
Memória liberada com sucesso.```