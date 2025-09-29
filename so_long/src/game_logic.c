/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:31:32 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/09/29 15:31:53 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	game->map[game->player_y][game->player_x] = '0';
	*next_pos = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	render_map(game);
}
