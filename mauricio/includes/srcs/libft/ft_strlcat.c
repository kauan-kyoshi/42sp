/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:54 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/24 16:48:17 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	i;
	size_t	ssize;
	size_t	dst_stopped;

	ssize = ft_strlen((char *)src);
	dst_stopped = ft_strlen(dst);
	if (dsize <= dst_stopped)
		return (ssize + dsize);
	i = 0;
	while (src[i] && (dst_stopped + i) < (dsize - 1))
	{
		dst[dst_stopped + i] = src[i];
		i++;
	}
	dst[dst_stopped + i] = '\0';
	return (dst_stopped + ssize);
}
