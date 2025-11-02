/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_cost.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:20:57 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 12:57:08 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_build_cost(t_dlist *stk)
{
	t_dnode	*pivot;
	size_t	pos;
	size_t	backward_cost;

	pos = 0;
	pivot = stk->head;
	while (pivot)
	{
		backward_cost = stk->size - pos;
		if (pos <= backward_cost)
		{
			ft_figure(pivot)->cost = pos;
			ft_figure(pivot)->is_mediam = TRUE;
		}
		else
		{
			ft_figure(pivot)->cost = backward_cost;
			ft_figure(pivot)->is_mediam = FALSE;
		}
		pos++;
		pivot = pivot->next;
	}
}
