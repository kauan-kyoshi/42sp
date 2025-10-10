/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:26:06 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/24 10:39:23 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	i;
	size_t	src_size;
	char	*duplicated;

	if (!src)
		return (NULL);
	i = 0;
	src_size = ft_strlen((char *)src);
	duplicated = (char *)malloc((src_size + 1) * sizeof(char));
	while (src[i])
	{
		duplicated[i] = src[i];
		i++;
	}
	duplicated[i] = '\0';
	return (duplicated);
}
