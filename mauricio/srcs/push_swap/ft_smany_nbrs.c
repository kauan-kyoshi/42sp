/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smany_nbrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:43:51 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 14:44:47 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_rotate_min_to_top(t_dlist **stk_a);

void	ft_smany_nbrs(t_dlist **stk_a, t_dlist **stk_b)
{
	t_target	*tgt;

	tgt = ft_calloc(1, sizeof(t_target));
	if (!tgt)
		return ;
	while ((*stk_a)->size > 3)
		ft_push(stk_a, stk_b, "pb");
	if (ft_is_ascending(*stk_a) == FALSE)
		ft_sthree_nbrs(stk_a);
	while ((*stk_b)->size > 0)
	{
		ft_build_cost(*stk_a);
		ft_build_cost(*stk_b);
		ft_find_best_target(*stk_a, *stk_b, &tgt);
		ft_handle_mmove(stk_a, stk_b, tgt);
		ft_push(stk_b, stk_a, "pa");
	}
	free(tgt);
	if (!ft_is_ascending(*stk_a))
		ft_rotate_min_to_top(stk_a);
}

static void	ft_rotate_min_to_top(t_dlist **stk_a)
{
	t_dnode		*min;
	size_t		cost;

	ft_build_cost(*stk_a);
	min = ft_find_min(*stk_a, NULL);
	cost = ft_figure(min)->cost;
	while (cost > 0)
	{
		if (ft_figure(min)->is_mediam)
			ft_rotate(stk_a, "ra");
		else
			ft_reverse_rotate(stk_a, "rra");
		cost--;
	}
}
