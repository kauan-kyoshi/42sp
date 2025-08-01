/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:58:32 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/08/01 17:58:36 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h> // Para malloc e free
# include <unistd.h> // Para read

/*
 * Se BUFFER_SIZE não for definido durante a compilação,
 * um valor padrão de 42 será usado.
 */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/*
 * Protótipo da função principal a ser entregue.
 */
char	*get_next_line(int fd);

/*
 * Protótipos das funções auxiliares que estarão em get_next_line_utils.c
 */
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);

#endif