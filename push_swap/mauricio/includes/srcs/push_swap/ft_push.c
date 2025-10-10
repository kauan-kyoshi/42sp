/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:46:04 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 14:54:48 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_handle_size(t_dlist **src, t_dlist **dst);

void	ft_push(t_dlist **src, t_dlist **dst, char *dsp)
{
	t_dnode	*head_b;

	if (!src || !(*src)->head)
		return ;
	head_b = (*src)->head;
	(*src)->head = head_b->next;
	if ((*src)->head)
		(*src)->head->prev = NULL;
	else
		(*src)->tail = NULL;
	if ((*dst)->head)
	{
		head_b->next = (*dst)->head;
		(*dst)->head->prev = head_b;
		(*dst)->head = head_b;
	}
	else
	{
		(*dst)->head = head_b;
		(*dst)->tail = head_b;
		head_b->next = NULL;
		head_b->prev = NULL;
	}
	ft_handle_size(src, dst);
	ft_putstrln_fd(dsp, STDOUT_FILENO);
}

static void	ft_handle_size(t_dlist **src, t_dlist **dst)
{
	(*dst)->size++;
	(*src)->size--;
}
