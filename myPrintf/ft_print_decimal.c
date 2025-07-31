/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:58:55 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/07/31 14:33:43 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


static int	ft_printnbr(int n)
{
	int		len;
	long	num;

	num = n;
	len = 0 ;
	if (num < 0)
	{
		len += write(1, "-", 1);
		num = -num;
	}
	if (n >= 10)
	{
		len += ft_printnbr(n / 10);
	}
	len += ft_print_char((num % 10) + '0');
	return (len);
}

int	ft_print_decimal(int n)
{
	if (n == 0)
		return (write(1, "0", 1));
	return (ft_printnbr(n));
}
