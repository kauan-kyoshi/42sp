/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:09:05 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/07/28 17:13:41 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

int	ft_printf(const char *format, ...);
int	ft_print_char(int c);
int	ft_print_string(char *s);
int	ft_print_pointer(void *ptr);
int	ft_print_decimal(int n);
int	ft_print_integer(int n);
int	ft_print_unsigned(unsigned int n);
int	ft_print_hex(unsigned int n, char format);

#endif