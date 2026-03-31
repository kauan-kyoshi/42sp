/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:29:17 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:42:11 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vect	compute_bump_perturbed_normal(t_obj *obj, t_vect surface_normal,
		float bump_u, float bump_v)
{
	t_vect	perturbed_normal;
	t_vect	tangent_u;
	t_vect	tangent_v;

	perturbed_normal = surface_normal;
	tangent_u = cross_product(surface_normal, obj->ey);
	tangent_v = cross_product(surface_normal, tangent_u);
	perturbed_normal = vector_add(perturbed_normal,
			vector_scale(tangent_u, bump_v));
	perturbed_normal = vector_add(perturbed_normal,
			vector_scale(tangent_v, bump_u));
	normalize_vector(&perturbed_normal);
	return (perturbed_normal);
}

void	apply_bump_map(t_obj *obj, t_img *img, t_hit *hit)
{
	char	*pixel_addr;
	int		tex_x[2];
	int		tex_y[2];
	int		height_sample[2];
	float	tex_uv[2];

	map_sphere_uv(obj, hit->phit, tex_uv);
	tex_x[0] = (((int)((1 - tex_uv[0]) * img->width))
			+ img->width / 2) % img->width;
	tex_y[0] = (int)((1 - tex_uv[1]) * img->height);
	tex_x[1] = (tex_x[0] + 1) % img->width;
	tex_y[1] = (tex_y[0] + 1) % img->height;
	pixel_addr = img->addr
		+ (tex_y[0] * img->line_length + tex_x[0] * (img->bits_per_pixel / 8));
	height_sample[0] = *((unsigned int *)pixel_addr) & 0xff;
	pixel_addr = img->addr
		+ (tex_y[0] * img->line_length + tex_x[1] * (img->bits_per_pixel / 8));
	height_sample[1] = *((unsigned int *)pixel_addr) & 0xff;
	tex_uv[0] = -((float)(height_sample[0] - height_sample[1])) / 10;
	pixel_addr = img->addr
		+ (tex_y[1] * img->line_length + tex_x[0] * (img->bits_per_pixel / 8));
	height_sample[1] = *((unsigned int *)pixel_addr) & 0xff;
	tex_uv[1] = -((float)(height_sample[0] - height_sample[1])) / 10;
	hit->nhit = compute_bump_perturbed_normal(obj, hit->nhit,
			tex_uv[0], tex_uv[1]);
}
