/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_order.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 00:55:09 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 18:39:58 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bool	ft_is_ascending(t_dlist *stk)
{
	t_dnode	*pvt;

	if (!stk || !stk->head || !stk->tail)
		return (FALSE);
	pvt = stk->head;
	while (pvt->next)
	{
		if (ft_figure(pvt)->value > ft_figure(pvt->next)->value)
			return (FALSE);
		pvt = pvt->next;
	}
	return (TRUE);
}

t_bool	ft_is_descending(t_dlist *stk)
{
	t_dnode	*pvt;

	if (!stk || !stk->head || !stk->tail)
		return (FALSE);
	pvt = stk->head;
	while (pvt->next)
	{
		if (ft_figure(pvt)->value < ft_figure(pvt->next)->value)
			return (FALSE);
		pvt = pvt->next;
	}
	return (TRUE);
}
