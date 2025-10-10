/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:27:21 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/24 09:22:59 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbr_length(int n)
{
	size_t			count;
	unsigned int	nbr;

	count = 0;
	if (n <= 0)
	{
		nbr = -n;
		count++;
	}
	else
		nbr = n;
	while (nbr > 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

static void	ft_nrb_convert_to_str(int n, char *s, size_t i)
{
	unsigned int	nbr;

	if (n < 0)
	{
		s[0] = '-';
		nbr = -n;
	}
	else
		nbr = n;
	while (nbr >= 10)
	{
		s[i--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	s[i] = (nbr % 10) + '0';
}

char	*ft_itoa(int n)
{
	size_t	length;
	char	*res;

	length = ft_nbr_length(n);
	res = (char *)malloc((length + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_nrb_convert_to_str(n, res, length - 1);
	res[length] = '\0';
	return (res);
}
