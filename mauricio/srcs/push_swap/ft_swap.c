/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:48:59 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 14:49:16 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(t_dlist **stk, char *dsp)
{
	t_dnode	*old_head;
	t_dnode	*next_old_head;

	if (!stk || !(*stk)->head || !(*stk)->head->next)
		return ;
	old_head = (*stk)->head;
	next_old_head = (*stk)->head->next;
	old_head->next = next_old_head->next;
	if (next_old_head->next)
		next_old_head->next->prev = old_head;
	else
		(*stk)->tail = old_head;
	next_old_head->prev = NULL;
	next_old_head->next = old_head;
	(*stk)->head = next_old_head;
	old_head->prev = next_old_head;
	ft_putstrln_fd(dsp, STDOUT_FILENO);
}
