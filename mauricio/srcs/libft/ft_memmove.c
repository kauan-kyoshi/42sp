/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:45:51 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/24 15:49:11 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d_bytes;
	unsigned char	*s_bytes;

	d_bytes = (unsigned char *)dst;
	s_bytes = (unsigned char *)src;
	if (dst > src)
	{
		i = n;
		while (i-- > 0)
			d_bytes[i] = s_bytes[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d_bytes[i] = s_bytes[i];
			i++;
		}
	}
	return (dst);
}
