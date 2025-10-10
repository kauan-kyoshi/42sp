/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_rotate_rotate.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:49:33 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/06 14:49:56 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_reverse_rotate_rotate(t_dlist **stk_a, t_dlist **stk_b, char *dsp)
{
	ft_reverse_rotate(stk_a, NULL);
	ft_reverse_rotate(stk_b, NULL);
	ft_putstrln_fd(dsp, STDOUT_FILENO);
}
