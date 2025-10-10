/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:29:35 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/24 15:44:03 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*aux;

	if (!s && n == 0)
		return (NULL);
	if (!c)
		c = 0;
	i = 0;
	aux = (unsigned char *)s;
	while (i < n)
	{
		aux[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
