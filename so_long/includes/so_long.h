/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:56:48 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/09/29 16:53:28 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define TILE_SIZE 32

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct s_img
{
	void	*ptr;
	int		width;	
	int		height;
}	t_img;

typedef struct s_game {
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		moves;
	t_img	wall;
	t_img	floor;
	t_img	player;
	t_img	collectible;
	t_img	exit;
}	t_game;

void	read_map(char *map_file, t_game *game);
void	validate_map(t_game *game);
void	validate_path(t_game *game);
void	init_graphics(t_game *game);
void	render_map(t_game *game);
void	init_hooks(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_close_window(t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
void	error_exit(char *message, t_game *game);
void	clean_exit(t_game *game);
void	free_map(char **map);

#endif