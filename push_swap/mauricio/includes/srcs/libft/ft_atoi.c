/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:32:50 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/25 08:51:39 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_isspace(const char c)
{
	return (c >= 9 && (c <= 13 || c == 32));
}

static int	check_isnum(const char c)
{
	return (c >= 48 && c <= 57);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] && check_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign *= -1;
	while (nptr[i] && check_isnum(nptr[i]))
	{
		res *= 10;
		res += nptr[i] % 48;
		i++;
	}
	return (res * sign);
}
