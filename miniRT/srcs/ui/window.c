/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:31:59 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:32:15 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	initialize_renderer(t_rt *rt, char *path)
{
	rt->mlx = mlx_init();
	if (!rt->width)
		rt->width = (float) WIN_WIDTH;
	if (!rt->height)
		rt->height = (float) WIN_HEIGHT;
	if (rt->height < rt->width)
		rt->aspectratio = rt->width / rt->height;
	else
		rt->aspectratio = rt->height / rt->width;
	rt->mlx_win = mlx_new_window(rt->mlx, rt->width, rt->height, "minirt");
	rt->path = path;
	rt->img.img = mlx_new_image(rt->mlx, rt->width, rt->height);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
			&rt->img.line_length, &rt->img.endian);
	rt->img.antialiasing_on = ANTIALIASING_ON;
	if (!rt->img.img)
		shutdown_renderer(rt);
	rt->img.addr_incr = rt->img.bits_per_pixel / 8;
	initialize_event_hooks(rt);
	rt->display_info = 0;
	rt->is_processing = FALSE;
}

void	shutdown_renderer(t_rt *rt)
{
	if (rt->mlx_win)
		mlx_destroy_window(rt->mlx, rt->mlx_win);
	if (rt->img.img)
		mlx_destroy_image(rt->mlx, rt->img.img);
	if (rt->mlx)
	{
		free(rt->mlx);
		rt->mlx = NULL;
	}
	destroy_renderer_state(rt);
	exit(0);
}

void	destroy_renderer_state(t_rt *rt)
{
	if (rt)
	{
		if (rt->light)
			destroy_lights(&rt->light);
		if (rt->objs)
			destroy_objects(rt, &rt->objs);
		free(rt);
	}
}
