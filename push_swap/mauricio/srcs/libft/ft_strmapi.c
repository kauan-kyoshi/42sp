/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:18:56 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/24 10:38:40 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *src, char (*f)(unsigned int, char))
{
	char	*newer;
	size_t	i;

	if (!src)
		return (NULL);
	newer = ft_strdup(src);
	if (!newer)
		return (NULL);
	i = 0;
	while (newer[i])
	{
		newer[i] = (*f)(i, newer[i]);
		i++;
	}
	return (newer);
}
