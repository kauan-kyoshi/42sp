/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_respecting_target.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 21:34:39 by mhidani           #+#    #+#             */
/*   Updated: 2025/09/28 10:02:09 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_place_on_begin(char *str, char sep, char tgt, char *find);
static char		*ft_place_on_last(char *str, char sep, char tgt, char *find);
static size_t	ft_count_tokens(char *str, char sep, char tgt);
static void		ft_extract_tokens(char *str, char sep, char tgt, char **split);

char	**ft_split_respecting_target(char *str, char sep, char tgt)
{
	size_t	size;
	char	**splited;

	if (!str || !sep || !tgt)
		return (NULL);
	size = ft_count_tokens(str, sep, tgt);
	if (size == 0)
		return (NULL);
	splited = ft_calloc(size + 1, sizeof(char *));
	if (!splited)
		return (NULL);
	ft_extract_tokens(str, sep, tgt, splited);
	return (splited);
}

static size_t	ft_count_tokens(char *str, char sep, char tgt)
{
	char	*begin;
	char	*pivot;
	char	find_target;
	size_t	count;

	begin = str;
	pivot = str;
	find_target = 0;
	count = 0;
	while (*pivot)
	{
		begin = ft_place_on_begin(pivot, sep, tgt, &find_target);
		pivot = ft_place_on_last(begin, sep, tgt, &find_target);
		if (*begin && pivot >= begin)
			count++;
		begin = pivot;
	}
	return (count);
}

static char	*ft_place_on_begin(char *str, char sep, char tgt, char *find)
{
	char	*pivot;

	pivot = str;
	while (*pivot && (*pivot == sep || *pivot == tgt))
	{
		if (*pivot == tgt)
			*find = 1;
		pivot++;
	}
	return (pivot);
}

static char	*ft_place_on_last(char *str, char sep, char tgt, char *find)
{
	char	*pivot;

	pivot = str;
	while (*pivot)
	{
		if (*find && *pivot == tgt)
			return (pivot);
		else if (!*find && *pivot == sep)
			return (pivot);
		pivot++;
	}
	return (pivot);
}

static void	ft_extract_tokens(char *str, char sep, char tgt, char **splited)
{
	char	find_target;
	char	*pivot;
	char	*begin;
	size_t	i;

	begin = str;
	pivot = str;
	find_target = 0;
	i = 0;
	while (*pivot)
	{
		begin = ft_place_on_begin(pivot, sep, tgt, &find_target);
		pivot = ft_place_on_last(begin, sep, tgt, &find_target);
		if (*begin && pivot >= begin)
		{
			splited[i] = ft_substr((char const *)begin, 0, pivot - begin);
			if (!splited[i])
			{
				splited[i] = NULL;
				return (ft_clean_tab((void **)splited));
			}
			i++;
		}
		begin = pivot;
	}
}
