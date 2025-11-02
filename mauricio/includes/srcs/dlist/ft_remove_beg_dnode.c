/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_beg_dnode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:56:00 by mhidani           #+#    #+#             */
/*   Updated: 2025/09/21 21:36:33 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	ft_remove_beg_dnode(t_dlist *list, void (*free_data)(void *))
{
	t_dnode	*head;

	if (!list || !free_data)
		return ;
	head = list->head;
	list->head->next->prev = NULL;
	list->head = list->head->next;
	free_data(head->data);
	free(head);
	list->size--;
}
