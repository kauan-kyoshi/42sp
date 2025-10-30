/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:00:04 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/16 18:37:54 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_c;

	i = 0;
	s_c = (unsigned char *)s;
	while (i < n)
	{
		if (s_c[i] == (unsigned char)c)
			return (&s_c[i]);
		i++;
	}
	return ((void *)0);
}
