/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:17:21 by kyoshi            #+#    #+#             */
/*   Updated: 2025/08/04 21:17:37 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Aloca e cria uma nova 'stash' com o conteúdo após a primeira nova linha.
// Esta versão é otimizada para passar na Norminette.
static char	*ft_create_new_stash(char *stash, char *newline_ptr)
{
	char	*new_stash;
	size_t	len;
	size_t	i;

	if (!newline_ptr || !*(newline_ptr + 1))
	{
		free(stash);
		return (NULL);
	}
	len = ft_strlen(newline_ptr + 1);
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

// Processa o buffer lido, juntando-o ao 'stash'.
static char	*ft_process_buffer(char *stash, char *buffer, ssize_t bytes_read)
{
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	return (stash);
}

// Lê do file descriptor e adiciona ao 'stash' até encontrar um '\n' ou EOF.
static char	*ft_read_and_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
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
		stash = ft_process_buffer(stash, buffer, bytes_read);
		if (!stash)
			break ;
	}
	free(buffer);
	return (stash);
}

// Função principal que lê uma linha de um file descriptor.
char	*get_next_line(int fd)
{
	static char	*stash[1024];
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
	stash[fd] = ft_create_new_stash(stash[fd], ft_strchr(stash[fd], '\n'));
	return (line);
}
