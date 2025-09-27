#include "../includes/so_long.h"

static void	load_texture(t_game *game, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&img->width, &img->height);
	if (!img->ptr)
		error_exit("Failed to load texture.", game);
}

void	init_graphics(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		error_exit("Failed to initialize mlx.", game);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE,
			"So Long");
	if (!game->win_ptr)
		error_exit("Failed to create window.", game);
	load_texture(game, &game->wall, "textures/wall.xpm");
	load_texture(game, &game->floor, "textures/floor.xpm");
	load_texture(game, &game->player, "textures/player.xpm");
	load_texture(game, &game->collectible, "textures/collectible.xpm");
	load_texture(game, &game->exit, "textures/exit.xpm");
}

static void	put_tile(t_game *game, char tile, int x, int y)
{
	void	*img_ptr;

	if (tile == '1')
		img_ptr = game->wall.ptr;
	else if (tile == 'P')
		img_ptr = game->player.ptr;
	else if (tile == 'C')
		img_ptr = game->collectible.ptr;
	else if (tile == 'E')
		img_ptr = game->exit.ptr;
	else // '0'
		img_ptr = game->floor.ptr;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		img_ptr, x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			put_tile(game, '0', x, y); // Desenha o chão primeiro
			put_tile(game, game->map[y][x], x, y);
			x++;
		}
		y++;
	}
}