/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_fwd_dlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:32:31 by mhidani           #+#    #+#             */
/*   Updated: 2025/09/23 14:26:02 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	ft_push_beg_dlist(t_dlist *list, void *data)
{
	t_dnode	*node;

	if (!list)
		return ;
	node = ft_create_dnode(data);
	if (!node)
		return ;
	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}
	list->size++;
}
