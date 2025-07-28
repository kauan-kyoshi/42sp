/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:08:40 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/07/28 17:12:46 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_print_pointer.c */
#include "ft_printf.h"

// Função auxiliar para imprimir o endereço do ponteiro em hexadecimal
static int	ft_putptr_len(unsigned long long n)
{
	int		len;
	char	*base;

	len = 0;
	base = "0123456789abcdef";
	if (n >= 16)
	{
		len += ft_putptr_len(n / 16);
	}
	len += ft_print_char(base[n % 16]);
	return (len);
}

int	ft_print_pointer(void *ptr)
{
	unsigned long long	p_addr;
	int					len;

	if (ptr == NULL)
		return (write(1, "(nil)", 5));

	p_addr = (unsigned long long)ptr;
	len = 0;
	len += write(1, "0x", 2);
	len += ft_putptr_len(p_addr);
	return (len);
}
