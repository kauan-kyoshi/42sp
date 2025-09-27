#include "../includes/so_long.h"

void	move_player(t_game *game, int new_x, int new_y)
{
	char	*next_pos;

	next_pos = &game->map[new_y][new_x];
	if (*next_pos == '1')
		return ;
	if (*next_pos == 'E' && game->collectibles == 0)
	{
		game->moves++;
		ft_printf("Moves: %d\n", game->moves);
		ft_printf("Congratulations, you won!\n");
		clean_exit(game);
	}
	else if (*next_pos == 'E' && game->collectibles != 0)
		return ;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	if (*next_pos == 'C')
		game->collectibles--;
	// Atualiza o mapa de caracteres
	game->map[game->player_y][game->player_x] = '0';
	*next_pos = 'P';
	// Atualiza a posição do jogador na struct
	game->player_x = new_x;
	game->player_y = new_y;
	// Redesenha a tela
	render_map(game);
}