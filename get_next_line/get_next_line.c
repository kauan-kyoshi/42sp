/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 18:00:19 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/08/01 18:00:21 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Atualiza o 'stash' para conter apenas os dados após a primeira nova linha.
// Libera o 'stash' antigo e retorna o novo.
static char	*ft_update_stash(char *stash)
{
	char	*new_stash;
	char	*newline_ptr;
	size_t	len;
	size_t	i;

	newline_ptr = ft_strchr(stash, '\n');
	if (!newline_ptr)
	{
		free(stash);
		return (NULL);
	}
	len = ft_strlen(newline_ptr + 1);
	if (len == 0)
	{
		free(stash);
		return (NULL);
	}
	new_stash = (char *)malloc((len + 1) * sizeof(char));
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	i = 0;
	while (newline_ptr[++i])
		new_stash[i - 1] = newline_ptr[i];
	new_stash[i - 1] = '\0';
	free(stash);
	return (new_stash);
}

// Extrai uma linha (até e incluindo '\n') do 'stash'.
static char	*ft_extract_line(char *stash)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (!stash || stash[0] == '\0')
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

// Lê do file descriptor e adiciona ao 'stash' até encontrar um '\n' ou EOF.
static char	*ft_read_and_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			stash = ft_strjoin(stash, buffer);
			if (!stash)
				break ;
		}
	}
	free(buffer);
	return (stash);
}

// Função principal que lê uma linha de um file descriptor.
char	*get_next_line(int fd)
{
	static char	*stash[1024]; // Array para suportar múltiplos FDs
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	stash[fd] = ft_read_and_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_extract_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = ft_update_stash(stash[fd]);
	return (line);
}