/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:33:27 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/09/29 17:21:11 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_shape_and_walls(t_game *game)
{
	int	i;
	int	j;

	game->map_width = ft_strlen(game->map[0]);
	i = 0;
	while (i < game->map_height)
	{
		if ((int)ft_strlen(game->map[i]) != game->map_width)
			error_exit("Map is not rectangular.", game);
		if (game->map[i][0] != '1' || game->map[i][game->map_width - 1] != '1')
			error_exit("Map is not enclosed by walls.", game);
		if (i == 0 || i == game->map_height - 1)
		{
			j = 0;
			while (j < game->map_width)
			{
				if (game->map[i][j] != '1')
					error_exit("Map is not enclosed by walls.", game);
				j++;
			}
		}
		i++;
	}
}

static char	process_tile_char(char tile_char, t_game *game, int x, int y)
{
	if (tile_char == 'P')
	{
		game->player_x = x;
		game->player_y = y;
	}
	else if (tile_char == 'C')
	{
		game->collectibles++;
	}
	else if (tile_char != 'E' && tile_char != '0' && tile_char != '1')
	{
		error_exit("Map contains invalid characters.", game);
	}
	return (tile_char);
}

static void	scan_row_for_components(t_game *game, int y, int *p_count,
int *e_count)
{
	int		x;
	char	current_tile;

	x = 0;
	while (x < game->map_width)
	{
		current_tile = process_tile_char(game->map[y][x], game, x, y);
		if (current_tile == 'P')
			(*p_count)++;
		else if (current_tile == 'E')
			(*e_count)++;
		x++;
	}
}

static void	check_components(t_game *game)
{
	int	y;
	int	p_count;
	int	e_count;

	p_count = 0;
	e_count = 0;
	game->collectibles = 0;
	y = 0;
	while (y < game->map_height)
	{
		scan_row_for_components(game, y, &p_count, &e_count);
		y++;
	}
	if (p_count != 1 || e_count != 1 || game->collectibles < 1)
		error_exit("Invalid map", game);
}

void	validate_map(t_game *game)
{
	check_shape_and_walls(game);
	check_components(game);
}
