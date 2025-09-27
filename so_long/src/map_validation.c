#include "../includes/so_long.h"

static void	check_shape_and_walls(t_game *game)
{
	int	i;

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
			int j = 0;
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

static void	check_components(t_game *game)
{
	int	y;
	int	x;
	int	p_count;
	int	e_count;

	p_count = 0;
	e_count = 0;
	game->collectibles = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				p_count++;
				game->player_x = x;
				game->player_y = y;
			}
			else if (game->map[y][x] == 'E')
				e_count++;
			else if (game->map[y][x] == 'C')
				game->collectibles++;
			else if (game->map[y][x] != '0' && game->map[y][x] != '1')
				error_exit("Map contains invalid characters.", game);
			x++;
		}
		y++;
	}
	if (p_count != 1 || e_count != 1 || game->collectibles < 1)
		error_exit("Map must have 1 Player, 1 Exit, and at least 1 Collectible.", game);
}

void	validate_map(t_game *game)
{
	check_shape_and_walls(game);
	check_components(game);
}