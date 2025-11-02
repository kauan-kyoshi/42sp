/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:35:47 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/25 10:34:10 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst_b;
	unsigned char	*src_b;

	if (!dst)
		return (0);
	if (!src || dst == src || n == 0)
		return (dst);
	i = 0;
	dst_b = (unsigned char *)dst;
	src_b = (unsigned char *)src;
	while (i < n)
	{
		dst_b[i] = src_b[i];
		i++;
	}
	return (dst);
}
