/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sfive_nbrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:40:32 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 18:47:19 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// static t_dnode	*ft_find_min(t_dlist *stk, t_dnode *exc);
static void		ft_handle_mins(t_dlist **stk_a, t_dlist **stk_b);
static void		ft_handle_chose_mov(t_dlist **stk_a, t_dnode *tgt);

void	ft_sfive_nbrs(t_dlist **stk_a, t_dlist **stk_b)
{
	ft_handle_mins(stk_a, stk_b);
	if (!ft_is_ascending(*stk_a))
		ft_sthree_nbrs(stk_a);
	if (!ft_is_descending(*stk_b))
		ft_swap(stk_b, "sb");
	ft_push(stk_b, stk_a, "pa");
	ft_push(stk_b, stk_a, "pa");
	if (!ft_is_ascending(*stk_a))
		ft_putstrln_fd("Error", STDOUT_FILENO);
}

t_dnode	*ft_find_min(t_dlist *stk, t_dnode *exc)
{
	t_dnode	*min;
	t_dnode	*pivot;

	min = stk->head;
	while (exc && min && min == exc)
		min = min->next;
	pivot = stk->head->next;
	while (pivot)
	{
		if (pivot != exc && ft_figure(pivot)->value < ft_figure(min)->value)
			min = pivot;
		pivot = pivot->next;
	}
	return (min);
}

static void	ft_handle_mins(t_dlist **stk_a, t_dlist **stk_b)
{
	t_dnode	*min_a;
	t_dnode	*min_b;
	t_dnode	*aux;

	min_a = ft_find_min(*stk_a, NULL);
	min_b = ft_find_min(*stk_a, min_a);
	ft_build_cost(*stk_a);
	if (ft_figure(min_a)->cost > ft_figure(min_b)->cost)
	{
		aux = min_a;
		min_a = min_b;
		min_b = aux;
	}
	ft_handle_chose_mov(stk_a, min_a);
	ft_push(stk_a, stk_b, "pb");
	ft_build_cost(*stk_a);
	ft_handle_chose_mov(stk_a, min_b);
	ft_push(stk_a, stk_b, "pb");
}

static void	ft_handle_chose_mov(t_dlist **stk_a, t_dnode *tgt)
{
	size_t	operations;

	if (!*stk_a || !tgt)
		return ;
	operations = 0;
	while (operations < ft_figure(tgt)->cost)
	{
		if (ft_figure(tgt)->is_mediam)
			ft_rotate(stk_a, "ra");
		else
			ft_reverse_rotate(stk_a, "rra");
		operations++;
	}
}
