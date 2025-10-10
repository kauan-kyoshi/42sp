/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:48:28 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 14:48:47 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_reverse_rotate(t_dlist **stk, char *dsp)
{
	t_dnode	*old_tail;

	if (!stk || !(*stk)->head || !(*stk)->tail)
		return ;
	if ((*stk)->head == (*stk)->tail)
		return ;
	old_tail = (*stk)->tail;
	(*stk)->tail = old_tail->prev;
	(*stk)->tail->next = NULL;
	(*stk)->head->prev = old_tail;
	old_tail->next = (*stk)->head;
	(*stk)->head = old_tail;
	ft_putstrln_fd(dsp, STDOUT_FILENO);
}
