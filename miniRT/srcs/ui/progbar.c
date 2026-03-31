/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progbar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:31:48 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:32:16 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_progress_box(t_rt *rt, int x, int y)
{
	int	w;
	int	h;
	int	tmp;

	x -= 20;
	y -= 20;
	tmp = y;
	w = PROGBAR_W + x;
	h = PROGBAR_H + y;
	while (x < w + 40)
	{
		y = tmp;
		while (y < h + 58)
		{
			mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, BLACK);
			y++;
		}
		x++;
	}
}

void	draw_progress_background(t_rt *rt, int x, int y)
{
	int	w;
	int	h;
	int	tmp;

	tmp = y;
	w = PROGBAR_W + x;
	h = PROGBAR_H + y;
	draw_progress_box(rt, x, y);
	while (x < w)
	{
		y = tmp;
		while (y < h)
		{
			mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, DARKGREY);
			y++;
		}
		x++;
	}
}

void	draw_progress_column(t_rt *rt, int x, int y)
{
	int	h;

	h = PROGBAR_H + y;
	while (y < h)
	{
		mlx_pixel_put(rt->mlx, rt->mlx_win, x, y, WHITE);
		y++;
	}
}

char	*build_progress_text(float percent)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(percent * 100);
	tmp2 = ft_strjoin("Processing: ", tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, "%");
	free(tmp2);
	return (tmp);
}

void	draw_progress_text(t_rt *rt, float perc)
{
	int	x;
	int	y;

	x = (rt->width * 0.5) - (PROGBAR_TEXT_W * 0.5);
	y = (rt->height * 0.5) + (PROGBAR_TEXT_H * 2);
	if (rt->process_text)
		mlx_string_put(rt->mlx, rt->mlx_win, x, y, BLACK, rt->process_text);
	rt->process_text = build_progress_text(perc);
	mlx_string_put(rt->mlx, rt->mlx_win, x, y, WHITE, rt->process_text);
}
