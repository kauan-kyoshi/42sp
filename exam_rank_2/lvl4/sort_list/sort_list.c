/*
Assignment name  : sort_list
Expected files   : sort_list.c
Allowed functions:
--------------------------------------------------------------------------------
Escreva a seguinte função:


t_list	*sort_list(t_list* lst, int (*cmp)(int, int));

Esta função deve ordenar a lista passada como parâmetro, usando o ponteiro de
função cmp para selecionar a ordem a ser aplicada, e retorna um ponteiro para
o primeiro elemento da lista ordenada.

As duplicações devem permanecer.
As entradas serão sempre consistentes.

Você deve usar o tipo t_list descrito no arquivo list.h que lhe é fornecido.
Você deve incluir esse arquivo (#include "list.h"), mas não deve entregá-lo.
Nós usaremos o nosso próprio [arquivo] para compilar o seu trabalho.
Funções passadas como cmp sempre retornarão um valor diferente de 0 se a e b
estiverem na ordem correta, e 0 caso contrário.

Por exemplo, a seguinte função usada como cmp irá ordenar a lista em ordem crescente:

int ascending(int a, int b)
{
	return (a <= b);
}```

*/
#include "ft_list.h"
#include "unistd.h"

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	int tmp;
	t_list *head;

	head = tmp;
	while (lst != NULL && lst->next != NULL)
	{
		if ((*cmp)(lst->data, lst->next->data) == 0)
		{
			tmp = lst->data;
			lst->data = lst->next->data;
			lst->next->data = tmp;
			lst = head;
		}
		else
			lst = lst->next;
	}
	return (head);
}
