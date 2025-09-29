/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:32:59 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/09/29 15:33:03 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long <map.ber>\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	read_map(argv[1], &game);
	validate_map(&game);
	validate_path(&game);
	init_graphics(&game);
	render_map(&game);
	init_hooks(&game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
