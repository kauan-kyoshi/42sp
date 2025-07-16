/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:51:23 by nde-sant          #+#    #+#             */
/*   Updated: 2025/06/08 10:39:47 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str);

int	ft_is_char_valid(char c);

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*remove_spaces(char *str)
{
	int		i;
	int		j;
	int		size;
	char	input[16];

	size = ft_strlen(str);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (ft_is_char_valid(str[i]))
		{
			input[j] = str[i];
			j++;
		}
		i += 2;
	}
	return (ft_strncpy(str, input, 17));
}

char	**create_matrix(char **dest_matrix)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		dest_matrix[i] = malloc(4);
		i++;
	}
	return (dest_matrix);
}

char	**get_input_matrix(char *input_str)
{
	char	**matrix;
	char	*formatted_str;
	int		i;
	int		col;
	int		row;

	matrix = malloc(4);
	create_matrix(matrix);
	formatted_str = remove_spaces(input_str);
	row = 0;
	i = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			matrix[row][col] = formatted_str[i];
			col++;
			i++;
		}
		row++;
	}
	return (matrix);
}
