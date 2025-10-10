/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_mov.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:46:20 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/05 13:08:23 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_move_both(t_dlist **stk_a, t_dlist **stk_b, t_sts_move *sts);
static void	ft_move_sing(t_dlist **stk_a, t_dlist **stk_b, t_sts_move *sts);

void	ft_handle_mmove(t_dlist **stk_a, t_dlist **stk_b, t_target *tgt)
{
	t_sts_move	*stats_move;

	stats_move = ft_calloc(1, sizeof(t_sts_move));
	if (!stats_move)
		return ;
	stats_move->med_a = ft_figure(tgt->a)->is_mediam;
	stats_move->med_b = ft_figure(tgt->b)->is_mediam;
	stats_move->cost_a = ft_figure(tgt->a)->cost;
	stats_move->cost_b = ft_figure(tgt->b)->cost;
	ft_move_both(stk_a, stk_b, stats_move);
	ft_move_sing(stk_a, stk_b, stats_move);
	free(stats_move);
}

static void	ft_move_both(t_dlist **stk_a, t_dlist **stk_b, t_sts_move *sts)
{
	while (sts->cost_a > 0 && sts->cost_b > 0 && sts->med_a && sts->med_b)
	{
		ft_rotate_rotate(stk_a, stk_b, "rr");
		sts->cost_a--;
		sts->cost_b--;
	}
	while (sts->cost_a > 0 && sts->cost_b > 0 && !sts->med_a && !sts->med_b)
	{
		ft_reverse_rotate_rotate(stk_a, stk_b, "rrr");
		sts->cost_a--;
		sts->cost_b--;
	}
}

static void	ft_move_sing(t_dlist **stk_a, t_dlist **stk_b, t_sts_move *sts)
{
	while (sts->cost_a > 0)
	{
		if (sts->med_a)
			ft_rotate(stk_a, "ra");
		else
			ft_reverse_rotate(stk_a, "rra");
		sts->cost_a--;
	}
	while (sts->cost_b > 0)
	{
		if (sts->med_b)
			ft_rotate(stk_b, "rb");
		else
			ft_reverse_rotate(stk_b, "rrb");
		sts->cost_b--;
	}
}

void	ft_handle_move(t_dlist **stk, t_dnode *tgt, char *name)
{
	char	*operation;

	if (ft_figure(tgt)->is_mediam == TRUE)
	{
		operation = ft_strjoin("r", name);
		ft_rotate(stk, operation);
	}
	else
	{
		operation = ft_strjoin("rr", name);
		ft_reverse_rotate(stk, operation);
	}
	free(operation);
}
