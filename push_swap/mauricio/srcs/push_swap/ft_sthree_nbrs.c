/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sthree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:04:12 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 14:44:47 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_dnode	*ft_get_max(t_dlist **stk);

void	ft_sthree_nbrs(t_dlist **stk)
{
	t_dnode	*max;

	max = ft_get_max(stk);
	if (max == (*stk)->head)
	{
		ft_swap(stk, "sa");
		ft_reverse_rotate(stk, "rra");
		if (!ft_is_ascending(*stk))
			ft_swap(stk, "sa");
	}
	else if (max == (*stk)->tail)
		ft_swap(stk, "sa");
	else
	{
		ft_reverse_rotate(stk, "rra");
		if (!ft_is_ascending(*stk))
			ft_swap(stk, "sa");
	}
}

static t_dnode	*ft_get_max(t_dlist **stk)
{
	t_dnode	*max;
	t_dnode	*pivot;

	pivot = (*stk)->head;
	max = (*stk)->head;
	while (pivot)
	{
		if (ft_figure(max)->value < ft_figure(pivot)->value)
			max = pivot;
		pivot = pivot->next;
	}
	return (max);
}
