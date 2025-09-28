#include "../includes/so_long.h"

// Função modificada para ser mais específica no erro
static void	load_texture(t_game *game, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&img->width, &img->height);
	if (!img->ptr)
	{
		// Imprime qual arquivo falhou antes de sair
		ft_printf("Error\nFailed to load texture: %s\n", path);
		clean_exit(game); // Usamos clean_exit para liberar o que já foi alocado
	}
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
	
	// Carrega cada textura. Se uma falhar, o programa agora dirá qual.
	load_texture(game, &game->wall, "textures/wall.xpm");
	load_texture(game, &game->floor, "textures/floor.xpm");
	load_texture(game, &game->player, "textures/player.xpm");
	load_texture(game, &game->collectible, "textures/collectible.xpm");
	load_texture(game, &game->exit, "textures/exit.xpm");
}

static void	put_tile(t_game *game, char tile, int x, int y)
{
	void	*img_to_draw;

	// PASSO 1: Desenha o chão opaco como fundo. SEMPRE. INCONDICIONALMENTE.
	// Isso garante que não haverá mais nenhum pixel preto da janela.
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->floor.ptr, x * TILE_SIZE, y * TILE_SIZE);

	// PASSO 2: Descobre se há algo para desenhar POR CIMA do chão.
	img_to_draw = NULL; // Começa como nulo por padrão.
	if (tile == '1')
		img_to_draw = game->wall.ptr;
	else if (tile == 'P')
		img_to_draw = game->player.ptr;
	else if (tile == 'C')
		img_to_draw = game->collectible.ptr;
	else if (tile == 'E')
		img_to_draw = game->exit.ptr;
	
	// PASSO 3: Se houver um objeto (parede, jogador, etc.), desenha-o agora.
	// Se for um espaço vazio ('0'), img_to_draw continuará nulo e nada mais será desenhado.
	if (img_to_draw != NULL)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			img_to_draw, x * TILE_SIZE, y * TILE_SIZE);
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
			put_tile(game, game->map[y][x], x, y);
			x++;
		}
		y++;
	}
}