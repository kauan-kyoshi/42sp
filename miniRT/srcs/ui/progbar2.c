/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progbar2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:31:53 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:32:16 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reset_progress_state(t_rt *rt)
{
	if (rt->process > rt->height - 1)
	{
		if (IS_LINUX)
		{
			mlx_clear_window(rt->mlx, rt->mlx_win);
			free(rt->process_text);
		}
		rt->process = 0;
	}
}

void	print_progress_console(float perc)
{
	printf("Processing : %*.2f%%\r", 6, perc * 100);
	fflush(stdout);
}

void	draw_progress_overlay(t_rt *rt)
{
	float	perc;
	int		bar_x;
	int		bar_y;

	bar_x = (rt->width * 0.5) - (PROGBAR_W / 2);
	bar_y = (rt->height * 0.5) - (PROGBAR_H / 2);
	pthread_mutex_lock(&rt->process_lock);
	rt->process += 1;
	perc = (rt->process / rt->height);
	print_progress_console(perc);
	if (IS_LINUX && rt->height > 100 && rt->width > PROGBAR_W)
	{
		if (rt->process == 1)
			draw_progress_background(rt, bar_x, bar_y);
		draw_progress_column(rt, bar_x + ((PROGBAR_W * perc)), bar_y);
		draw_progress_text(rt, perc);
	}
	reset_progress_state(rt);
	pthread_mutex_unlock(&rt->process_lock);
}
