#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h" // Ajuste o caminho se necessário

// --- Constantes ---
# define TILE_SIZE 32 // Tamanho de cada tile em pixels

// Keycodes para Linux (podem variar em macOS)
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

// --- Estruturas de Dados ---

// Estrutura para guardar ponteiros de imagem
typedef struct s_img {
	void	*ptr;
	int		width;
	int		height;
}	t_img;

// Estrutura principal do jogo
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

// --- Protótipos de Função ---

// 01_map_reader.c
void	read_map(char *map_file, t_game *game);

// 02_map_validation.c
void	validate_map(t_game *game);

// 03_path_validation.c
void	validate_path(t_game *game);

// 04_graphics.c
void	init_graphics(t_game *game);
void	render_map(t_game *game);

// 05_hooks.c
void	init_hooks(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_close_window(t_game *game);

// 06_game_logic.c
void	move_player(t_game *game, int new_x, int new_y);

// 07_cleanup.c
void	error_exit(char *message, t_game *game);
void	clean_exit(t_game *game);
void	free_map(char **map);

#endif