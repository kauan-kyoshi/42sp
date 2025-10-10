/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_best_target.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:10:48 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 14:10:50 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_dnode	*ft_find_target_in_a(t_dlist *stk_a, int value_b);
static size_t	ft_find_crr_cost(t_dnode *tgt, t_dnode *pvt_b);

void	ft_find_best_target(t_dlist *stk_a, t_dlist *stk_b, t_target **tgt)
{
	t_dnode	*pivot_b;
	t_dnode	*target_a;
	size_t	best_cost;
	size_t	current_cost;

	pivot_b = stk_b->head;
	best_cost = ~(1 << (sizeof(int) * 8 - 1));
	while (pivot_b)
	{
		target_a = ft_find_target_in_a(stk_a, ft_figure(pivot_b)->value);
		current_cost = ft_find_crr_cost(target_a, pivot_b);
		if (current_cost < best_cost)
		{
			(*tgt)->a = target_a;
			(*tgt)->b = pivot_b;
			(*tgt)->best_cost = current_cost;
			best_cost = current_cost;
		}
		pivot_b = pivot_b->next;
	}
}

static t_dnode	*ft_find_target_in_a(t_dlist *stk_a, int value_b)
{
	t_dnode	*pivot_a;
	t_dnode	*target;
	int		min_diff;
	int		diff;

	pivot_a = stk_a->head;
	target = NULL;
	min_diff = ~(1 << (sizeof(int) * 8 - 1));
	while (pivot_a)
	{
		diff = ft_figure(pivot_a)->value - value_b;
		if (diff > 0 && diff < min_diff)
		{
			min_diff = diff;
			target = pivot_a;
		}
		pivot_a = pivot_a->next;
	}
	if (!target)
		target = ft_find_min(stk_a, NULL);
	return (target);
}

static size_t	ft_find_crr_cost(t_dnode *tgt, t_dnode *pvt_b)
{
	size_t	cost_a;
	size_t	cost_b;
	t_bool	both_above;
	t_bool	both_below;

	cost_a = ft_figure(tgt)->cost;
	cost_b = ft_figure(pvt_b)->cost;
	both_above = ft_figure(tgt)->is_mediam && ft_figure(pvt_b)->is_mediam;
	both_below = !ft_figure(tgt)->is_mediam && !ft_figure(pvt_b)->is_mediam;
	if (both_above || both_below)
	{
		if (cost_a > cost_b)
			return (cost_a);
		else
			return (cost_b);
	}
	else
		return (cost_a + cost_b);
}
