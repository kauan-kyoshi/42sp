/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:31:03 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_window_close(t_rt *rt)
{
	shutdown_renderer(rt);
	exit(0);
	return (0);
}

static int	idle_loop_noop(t_rt *rt)
{
	(void) rt;
	return (0);
}

void	initialize_event_hooks(t_rt *rt)
{
	ft_memset(rt->event.key, 0, MAX_KEY);
	mlx_loop_hook(rt->mlx, idle_loop_noop, rt);
	mlx_hook(rt->mlx_win, ON_KEYDOWN, 1L << 0, on_key_down, rt);
	mlx_hook(rt->mlx_win, ON_KEYUP, 1L << 1, on_key_up, rt);
	mlx_hook(rt->mlx_win, ON_DESTROY, 0L, handle_window_close, rt);
}
