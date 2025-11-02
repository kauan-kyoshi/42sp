/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexof_dlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 21:11:20 by mhidani           #+#    #+#             */
/*   Updated: 2025/09/21 21:36:14 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

size_t	ft_indexof_dlist(t_dlist *list, t_dnode *target)
{
	size_t	idx;
	t_dnode	*pivot;

	if (!list || !target)
		return (0);
	pivot = list->head;
	idx = 0;
	while (pivot->next != NULL)
	{
		if (pivot == target)
			break ;
		idx++;
		pivot = pivot->next;
	}
	return (idx);
}
