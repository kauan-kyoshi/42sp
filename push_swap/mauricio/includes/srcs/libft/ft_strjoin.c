/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:38:40 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/25 08:41:24 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_length;
	size_t	s2_length;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	s1_length = ft_strlen((char *)s1);
	s2_length = ft_strlen((char *)s2);
	res = (char *)malloc((s1_length + s2_length + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, (char *)s1, (s1_length + 1));
	ft_strlcat(res, s2, (s1_length + s2_length + 1));
	return (res);
}
