/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:32:42 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/09/29 15:32:54 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (0);
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
	render_map(game);
	mlx_key_hook(game->win_ptr, handle_keypress, game);
	mlx_hook(game->win_ptr, 17, 0, handle_close_window, game);
}
