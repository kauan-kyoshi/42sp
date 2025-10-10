/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:36:51 by mhidani           #+#    #+#             */
/*   Updated: 2025/09/25 11:44:52 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_tokens(char const *s, char c);
static char		*start_pivot(char const *s, char c);
static char		*end_pivot(char const *s, char c);
static char		*get_token(char *pivot, char *end, char **tokens, size_t size);

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	size;
	char	*start;
	char	*end;
	char	**tokens;

	if (!s)
		return (NULL);
	size = count_tokens(s, c);
	tokens = malloc((size + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	while (*s && i < size)
	{
		start = start_pivot(s, c);
		end = end_pivot(start, c);
		tokens[i] = get_token(start, end, tokens, size);
		if (!tokens[i++])
			return (NULL);
		s = end;
	}
	tokens[size] = NULL;
	return (tokens);
}

static size_t	count_tokens(char const *s, char c)
{
	int		in_token;
	size_t	count;

	in_token = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && !in_token)
		{
			in_token = 1;
			count++;
		}
		else if (*s == c)
			in_token = 0;
		s++;
	}
	return (count);
}

static char	*start_pivot(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	if (*s && *s != c)
		return ((char *)s);
	return (NULL);
}

static char	*end_pivot(char const *s, char c)
{
	while (*s && *s != c)
		s++;
	return ((char *)s);
}

static char	*get_token(char *pivot, char *end, char **tokens, size_t size)
{
	char	*token;
	size_t	i;

	i = 0;
	if (!pivot || !end)
		return (NULL);
	if (!*end)
		while (pivot[i])
			i++;
	else
		while (pivot[i] && pivot[i] != *end)
			i++;
	token = malloc((i + 1) * sizeof(char));
	if (!token)
	{
		i = 0;
		while (i < size)
			free(tokens[i++]);
		free(tokens);
		return (NULL);
	}
	ft_strlcpy(token, pivot, i + 1);
	return (token);
}
