/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_figure_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:54:06 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/05 16:20:11 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_figure	*ft_figure(t_dnode *node)
{
	if (!node || !node->data)
		return (NULL);
	return (((t_figure *)node->data));
}

void	ft_clean_figure(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
}
