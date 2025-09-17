/*
Assignment name  : ft_list_foreach
Expected files   : ft_list_foreach.c, ft_list.h
Allowed functions:
--------------------------------------------------------------------------------

Escreva uma função que receba uma lista e um ponteiro de função, e aplique esta função a cada elemento da lista.

Ela deve ser declarada da seguinte forma:


void    ft_list_foreach(t_list *begin_list, void (*f)(void *));

A função apontada por f será usada da seguinte forma:


(*f)(list_ptr->data);

Você deve usar a seguinte estrutura, e entregá-la em um arquivo chamado ft_list.h:

typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;
*/
#include "ft_list.h"

void    ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	 t_list *current_node;

    // Se a lista ou o ponteiro de função for nulo, não há nada a fazer.
    if (!begin_list || !f)
    {
        return;
    }

    // Começa pelo primeiro elemento da lista.
    current_node = begin_list;

    // Percorre a lista até o final (onde 'next' é NULL).
    while (current_node != NULL)
    {
        // Aplica a função 'f' ao campo 'data' do nó atual.
        (*f)(current_node->data);
        
        // Avança para o próximo nó da lista.
        current_node = current_node->next;
    }
}