/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:31:16 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:42:11 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	sample_texture_color(t_img *img, float xf, float yf)
{
	char	*dst;
	int		x;
	int		y;

	x = ((int)((1 - xf) * img->width) + img->width / 2) % img->width;
	y = (int)((1 - yf) * img->height);
	if (0 <= x && x < img->width && 0 <= y && y < img->height)
	{
		dst = img->addr
			+ (y * img->line_length + x * (img->bits_per_pixel / 8));
		return (unpack_rgb_color(*(unsigned int *)dst));
	}
	return (make_color(0, 0, 0));
}

void	*render_thread_routine(void *line_trd)
{
	float		x;
	float		y;
	char		*pix;
	t_line_trd	*ltrd;

	ltrd = (t_line_trd *) line_trd;
	y = ltrd->i;
	pix = ltrd->rt->img.addr;
	pix += ltrd->rt->img.line_length * ltrd->i;
	while (y < ltrd->rt->height)
	{
		x = -1;
		while (++x < ltrd->rt->width)
		{
			*(unsigned int *)pix = trace_primary_ray(ltrd->rt, x, y);
			pix += ltrd->rt->img.addr_incr;
		}
		y += MAX_THREADS;
		pix += ltrd->rt->img.line_length * (MAX_THREADS - 1);
		draw_progress_overlay(ltrd->rt);
	}
	return (NULL);
}

void	render_multithreaded(t_rt *rt)
{
	int			i;
	t_line_trd	lines[MAX_THREADS];

	i = 0;
	normalize_scene_objects(rt);
	while (i < MAX_THREADS)
	{
		lines[i].i = i;
		lines[i].rt = rt;
		pthread_create(&lines[i].trd, NULL, render_thread_routine, &lines[i]);
		i++;
	}
	i = 0;
	while (i < MAX_THREADS)
		pthread_join(lines[i++].trd, NULL);
}

int	trace_primary_ray(t_rt *rt, float x, float y)
{
	t_rays	r;

	if (rt->img.antialiasing_on)
		return (sample_antialiasing(rt, x, y));
	build_camera_ray(rt, &r.prime_ray, x, y);
	return (pack_rgb_color(trace_ray(rt, &r, MAX_REFLECT)));
}

void	render_frame(t_rt *rt)
{
	if (rt->is_processing)
		return ;
	rt->is_processing = TRUE;
	get_elapsed_seconds();
	render_multithreaded(rt);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img.img, 0, 0);
	if (rt->display_info)
		draw_help_overlay(rt);
	printf("\nDuration   :   %.2fs\n", get_elapsed_seconds());
	fflush(stdout);
	rt->is_processing = FALSE;
}
