#include "../includes/so_long.h"

int	handle_keypress(int keycode, t_game *game)
{
	int	x;
	int	y;

	x = game->player_x;
	y = game->player_y;
	if (keycode == KEY_ESC)
		clean_exit(game);
	else if (keycode == KEY_W)
		y--;
	else if (keycode == KEY_A)
		x--;
	else if (keycode == KEY_S)
		y++;
	else if (keycode == KEY_D)
		x++;
	else
		return (0); // Nenhuma tecla de movimento foi pressionada
	move_player(game, x, y);
	return (0);
}

int	handle_close_window(t_game *game)
{
	clean_exit(game);
	return (0);
}

void	init_hooks(t_game *game)
{
	render_map(game); // Desenha o mapa inicial
	mlx_key_hook(game->win_ptr, handle_keypress, game);
	mlx_hook(game->win_ptr, 17, 0, handle_close_window, game);
}