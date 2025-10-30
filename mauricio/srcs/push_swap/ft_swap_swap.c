/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:50:34 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 14:50:48 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap_swap(t_dlist **stk_a, t_dlist **stk_b, char *dsp)
{
	ft_swap(stk_a, NULL);
	ft_swap(stk_b, NULL);
	ft_putstrln_fd(dsp, STDOUT_FILENO);
}
