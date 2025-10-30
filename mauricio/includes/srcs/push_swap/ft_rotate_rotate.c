/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:50:11 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 14:50:24 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rotate_rotate(t_dlist **stk_a, t_dlist **stk_b, char *dsp)
{
	ft_rotate(stk_a, NULL);
	ft_rotate(stk_b, NULL);
	ft_putstrln_fd(dsp, STDOUT_FILENO);
}
