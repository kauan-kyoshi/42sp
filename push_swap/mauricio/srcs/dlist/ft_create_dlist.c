/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_dlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:07:30 by mhidani           #+#    #+#             */
/*   Updated: 2025/09/30 16:15:09 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

t_dlist	*ft_create_dlist(t_dnode *node)
{
	t_dlist	*list;

	list = malloc(sizeof(t_dlist));
	if (!list)
		return (NULL);
	list->head = node;
	list->tail = node;
	list->size = 0;
	if (node)
		list->size = 1;
	return (list);
}
