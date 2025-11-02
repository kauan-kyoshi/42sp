/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:58:10 by mhidani           #+#    #+#             */
/*   Updated: 2025/07/25 11:45:22 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	exists_in(char const target, char const *set)
{
	size_t	i;

	if (!target || !set)
		return (-1);
	i = 0;
	while (set[i])
	{
		if (set[i] == target)
			return (1);
		i++;
	}
	return (0);
}

static size_t	get_start(char const *src, char const *set)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (!exists_in(src[i], set))
			return (i);
		i++;
	}
	return (i);
}

static size_t	get_end(char const *src, char const *set)
{
	size_t	i;

	i = ft_strlen(src) - 1;
	while (i > 0)
	{
		if (!exists_in(src[i], set))
			return (i + 1);
		i--;
	}
	return (i);
}

static char	*alloc_empty(void)
{
	char	*res;

	res = (char *)malloc(1 * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '\0';
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*res;

	start = get_start(s1, set);
	end = get_end(s1, set);
	if (start > end)
		return (alloc_empty());
	res = (char *)malloc((end - start + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < (end - start))
	{
		res[i] = s1[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
