/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:05 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:47 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

int	copy_top_value(t_dlist *from, int **out)
{
	int	*value_copy; /* ponteiro para armazenar a cópia do valor */

	value_copy = malloc(sizeof(int)); /* aloca memória para um int */
	if (!value_copy) /* se malloc falhou */
		return (0); /* retorna 0 (falha) */
	*value_copy = *((int *)(from->head->data)); /* copia o valor do topo para a nova alocação */
	*out = value_copy; /* atribui o ponteiro ao parâmetro de saída */
	return (1); /* retorna 1 (sucesso) */
}

void	detach_head_node(t_dlist *from)
{
	t_dnode	*node; /* ponteiro para o nó a ser removido */

	node = from->head; /* salva o primeiro nó */
	if (from->head == from->tail) /* se há apenas um nó (head == tail) */
	{
		from->head = NULL; /* pilha fica vazia */
		from->tail = NULL; /* pilha fica vazia */
		from->size = 0; /* tamanho = 0 */
	}
	else /* se há mais de um nó */
	{
		from->head = from->head->next; /* novo head é o segundo nó */
		if (from->head) /* valida se head não é nulo */
			from->head->prev = NULL; /* novo head não tem anterior */
		from->size--; /* decrementa tamanho */
	}
	free_int(node->data); /* libera o dados do nó (int alocado) */
	free(node); /* libera a estrutura do nó */
}

void	push_value_to_dest(t_dlist *to, int *value_copy)
{
	if (to->head == NULL) /* se a pilha destino está vazia */
	{
		to->head = ft_create_dnode(value_copy); /* cria novo nó com o valor */
		to->tail = to->head; /* é ao mesmo tempo head e tail */
		to->size = 1; /* tamanho = 1 */
	}
	else /* se a pilha destino já tem elementos */
		ft_push_beg_dlist(to, value_copy); /* insere o novo nó no início (topo) */
}
