/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:45:59 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:01:36 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	msg_quit(char *s)
{
	ft_putendl_fd(s, 1);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_rt	*rt;

	rt = ft_calloc(sizeof(t_rt), 1);
	if (argc != 2)
		report_error(MSG_USAGE);
	else if (load_scene_file(rt, argv[1]))
	{
		initialize_renderer(rt, argv[1]);
		render_frame(rt);
		mlx_loop(rt->mlx);
	}
	destroy_renderer_state(rt);
	return (0);
}
