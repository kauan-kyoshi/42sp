/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:47:52 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 14:48:11 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rotate(t_dlist **stk, char *dsp)
{
	t_dnode	*old_head;

	if (!stk || !(*stk)->head || !(*stk)->tail)
		return ;
	if ((*stk)->head == (*stk)->tail)
		return ;
	old_head = (*stk)->head;
	(*stk)->head = old_head->next;
	(*stk)->head->prev = NULL;
	old_head->next = NULL;
	old_head->prev = (*stk)->tail;
	(*stk)->tail->next = old_head;
	(*stk)->tail = old_head;
	ft_putstrln_fd(dsp, STDOUT_FILENO);
}
