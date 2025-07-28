/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:08:49 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/07/28 17:08:50 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format_handler(const char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (specifier == 's')
		return (ft_print_string(va_arg(args, char *)));
	else if (specifier == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_print_decimal(va_arg(args, int)));
	else if (specifier == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (specifier == 'x' || specifier == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), specifier));
	else if (specifier == '%')
		return (ft_print_char('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		total_length;

	i = 0;
	total_length = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			total_length += ft_format_handler(format[i], args);
		}
		else
		{
			total_length += write(1, &format[i], 1);
		}
		i++;
	}
	va_end(args);
	return (total_length);
}