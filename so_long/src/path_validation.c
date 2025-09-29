/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:36:49 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/09/29 15:37:25 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	**duplicate_map(t_game *game)
{
	char	**copy;
	int		i;

	copy = ft_calloc(game->map_height + 1, sizeof(char *));
	if (!copy)
		error_exit("Memory allocation failed for map copy.", game);
	i = 0;
	while (i < game->map_height)
	{
		copy[i] = ft_strdup(game->map[i]);
		if (!copy[i])
		{
			free_map(copy);
			error_exit("Memory allocation failed for map copy.", game);
		}
		i++;
	}
	return (copy);
}

static void	flood_fill(char **map_copy, int x, int y, t_game *game)
{
	if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width
		|| map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return ;
	map_copy[y][x] = 'F';
	flood_fill(map_copy, x + 1, y, game);
	flood_fill(map_copy, x - 1, y, game);
	flood_fill(map_copy, x, y + 1, game);
	flood_fill(map_copy, x, y - 1, game);
}

static void	check_path_result(char **map_copy, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
			{
				free_map(map_copy);
				error_exit("Invalid path.", game);
			}
			x++;
		}
		y++;
	}
}

void	validate_path(t_game *game)
{
	char	**map_copy;

	map_copy = duplicate_map(game);
	flood_fill(map_copy, game->player_x, game->player_y, game);
	check_path_result(map_copy, game);
	free_map(map_copy);
}
