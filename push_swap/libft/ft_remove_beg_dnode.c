/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_beg_dnode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:56:00 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/30 15:16:14 by kakubo-l         ###   ########.fr       */
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
