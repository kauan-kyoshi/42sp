/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:21:54 by nde-sant          #+#    #+#             */
/*   Updated: 2025/06/08 19:05:42 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_putstr(char *str);

void	ft_putmatrix(char **str, int lines);

int		ft_is_input_valid(char *str);

char	**create_matrix(char **dest_matrix);

char	**get_input_matrix(char *input_str);

void	fill_fours(char **origin_matrix, char **dest_matrix);

void	fill_ones(char **origin_matrix, char **dest_matrix);

int		valid_game(char **matrix);

int	main(int argc, char **argv)
{
	char	**input_matrix;
	char	**dest_matrix;

	if (argc == 2 && ft_is_input_valid(argv[1]))
	{
		input_matrix = get_input_matrix(argv[1]);
		if (valid_game(input_matrix) == 1)
		{
			dest_matrix = malloc(4);
			create_matrix(dest_matrix);
			fill_fours(input_matrix, dest_matrix);
			fill_ones(input_matrix, dest_matrix);
			ft_putmatrix(dest_matrix, 4);
		}
		else
		{
			ft_putstr("Error\n");
		}
	}
	else
	{
		ft_putstr("Error\n");
	}
}
