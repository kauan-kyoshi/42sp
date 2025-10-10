/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:05:19 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/24 17:17:08 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*aux;

	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)(s + ft_strlen((char *)s)));
	aux = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			aux = (char *)s;
		s++;
		if (aux && !*s)
			return (aux);
	}
	return (NULL);
}
