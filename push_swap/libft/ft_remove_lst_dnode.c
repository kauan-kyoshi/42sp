/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_lst_dnode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:57:09 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/30 15:16:19 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	ft_remove_lst_dnode(t_dlist *list, void (*free_data)(void *))
{
	t_dnode	*tail;

	if (!list || !free_data)
		return ;
	tail = list->tail;
	list->tail->prev->next = NULL;
	list->tail = list->tail->prev;
	free_data(tail->data);
	free(tail);
	list->size--;
}
