/*
Assignment name  : ft_list_remove_if
Expected files   : ft_list_remove_if.c
Allowed functions: free
--------------------------------------------------------------------------------

Escreva uma função chamada ft_list_remove_if que remove da lista passada todo
elemento cujo dado (data) seja "igual" ao dado de referência.
Ela deve ser declarada da seguinte forma:

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());

cmp recebe dois void* e retorna 0 quando ambos os parâmetros são iguais.
Você deve usar o arquivo ft_list.h, que conterá:

$>cat ft_list.h
typedef struct      s_list
{
    struct s_list   *next;
    void            *data;
}                   t_list;
$>
*/

#include "ft_list.h"
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	if (begin_list == NULL || data_ref == NULL || cmp == NULL)
	{
		return;
	}

	t_list *current_node = *begin_list;
	
	while (current_node != NULL && cmp(current_node->data,data_ref) == 0)
	{
		*begin_list = current_node->next;
		free(current_node);
		current_node = *begin_list;
	}
	while (current_node != NULL && current_node->next != NULL)
	{
		if (cmp(current_node->next->data, data_ref) == 0)
		{
			t_list *node_to_remove = current_node->next;
			current_node->next = node_to_remove->next;
			free(node_to_remove->next);
		}
		else
		{
			current_node = current_node->next;
		}
	}
}