/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_dlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:58:08 by mhidani           #+#    #+#             */
/*   Updated: 2025/09/28 15:39:48 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

void	ft_clean_dlist(t_dlist **list, void (*free_data)(void *))
{
	t_dnode	*tmp;
	t_dnode	*pivot;

	if (!list || !free_data)
		return ;
	pivot = (*list)->head;
	while (pivot != NULL)
	{
		tmp = pivot;
		pivot = pivot->next;
		free_data(tmp->data);
		free(tmp);
	}
	free(*list);
	*list = NULL;
}
