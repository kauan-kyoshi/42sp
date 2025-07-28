/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:08:31 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/07/28 17:12:04 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex_len(unsigned int n, const char *base)
{
	int	len;

	len = 0;
	if (n >= 16)
	{
		len += ft_puthex_len(n / 16, base);
	}
	len += ft_print_char(base[n % 16]);
	return (len);
}

int	ft_print_hex(unsigned int n, char format)
{
	if (n == 0)
		return (write(1, "0", 1));
	if (format == 'x')
		return (ft_puthex_len(n, "0123456789abcdef"));
	else
		return (ft_puthex_len(n, "0123456789ABCDEF"));
}