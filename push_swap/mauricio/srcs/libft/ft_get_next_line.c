/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:53:06 by mhidani           #+#    #+#             */
/*   Updated: 2025/09/22 11:46:07 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_end(char *s);
static char		*ft_accumulator(int fd, char *stash);
static char		*ft_extract_line(char *stash);
static char		*ft_safe_clean(char *stash);

char	*ft_get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = ft_calloc(1, 1);
		if (!stash)
			return (NULL);
	}
	stash = ft_accumulator(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	stash = ft_safe_clean(stash);
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
	}
	return (line);
}

static size_t	ft_end(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static char	*ft_accumulator(int fd, char *stash)
{
	char	*buffer;
	char	*tmp;
	ssize_t	bread;

	buffer = ft_calloc(1, BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bread = 1;
	while (!ft_strchr(stash, '\n') && bread > 0)
	{
		bread = read(fd, buffer, BUFFER_SIZE);
		if (bread < 0)
			return (free(buffer), free(stash), NULL);
		buffer[bread] = '\0';
		tmp = ft_strjoin(stash, buffer);
		free(stash);
		stash = tmp;
	}
	free(buffer);
	return (stash);
}

static char	*ft_extract_line(char *stash)
{
	size_t	i;
	size_t	end;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	end = ft_end(stash);
	if (stash[end] == '\n')
		end++;
	line = ft_calloc(1, end + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && i < end)
	{
		line[i] = stash[i];
		i++;
	}
	return (line);
}

static char	*ft_safe_clean(char *stash)
{
	size_t	i;
	size_t	end;
	char	*new;

	end = ft_end(stash);
	if (!stash[end])
		return (free(stash), NULL);
	new = ft_calloc(1, ft_strlen(stash) - end);
	if (!new)
		return (NULL);
	end++;
	i = 0;
	while (stash[end])
		new[i++] = stash[end++];
	free(stash);
	return (new);
}
