/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:08:25 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/07/28 17:11:41 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_len(int n)
{
	int		len;
	long	num;

	len = 0;
	num = n;
	if (num < 0)
	{
		len += write(1, "-", 1);
		num = -num;
	}
	if (num >= 10)
	{
		len += ft_putnbr_len(num / 10);
	}
	len += ft_print_char((num % 10) + '0');
	return (len);
}

int	ft_print_decimal(int n)
{
	if (n == 0)
		return (write(1, "0", 1));
	return (ft_putnbr_len(n));
}

int	ft_print_integer(int n)
{
	return (ft_print_decimal(n));
}
