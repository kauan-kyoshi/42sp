/*
Assignment name  : ft_list_size
Expected files   : ft_list_size.c, ft_list.h
Allowed functions:
--------------------------------------------------------------------------------

Escreva uma função que retorne o número de elementos na lista encadeada que é
passada para ela.
Ela deve ser declarada da seguinte forma:

int	ft_list_size(t_list *begin_list);

Você deve usar a seguinte estrutura, e entregá-la em um arquivo chamado ft_list.h:

typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;
*/

#include "ft_list.h"

int	ft_list_size(t_list *begin_list)
{
	t_list *now;
	int i = 0;
	now = begin_list;

	while (now != NULL)
	{
		i++;
		now = now->next;
	}
	return(i);
}
