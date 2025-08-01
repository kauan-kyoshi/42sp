/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:03:41 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/08/01 13:06:04 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putunbr_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
	{
		len += ft_putunbr_len(n / 10);
	}
	len += ft_print_char((n % 10) + '0');
	return (len);
}

int	ft_print_unsigned(unsigned int n)
{
	if (n == 0)
		return (write(1, "0", 1));
	return (ft_putunbr_len(n));
}
