/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:30:03 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	map_pattern_uv(t_obj *obj, t_vect hit_point, float mapped_uv[3])
{
	if (obj->id == id_plane)
		map_plane_uv(obj, hit_point, mapped_uv);
	if (obj->id == id_sphere)
		map_sphere_uv(obj, hit_point, mapped_uv);
	if (obj->id == id_cylinder || obj->id == id_cone)
		map_cylindrical_uv(obj, hit_point, mapped_uv);
}

static t_color	resolve_basic_pattern(t_obj *obj, float mapped_uv[3])
{
	if (obj->pattern_num == 1 && (((int)(mapped_uv[0] * obj->pattern_len)
			+ (int)(mapped_uv[1] * obj->pattern_len)) & 1))
		return (obj->color);
	if (obj->pattern_num == 2 && ((int)(mapped_uv[0] * obj->pattern_len) & 1))
		return (obj->color);
	if (obj->pattern_num == 3 && ((int)(mapped_uv[1] * obj->pattern_len) & 1))
		return (obj->color);
	if (obj->pattern_num < 4)
		return (obj->color2);
	mapped_uv[2] = sin(mapped_uv[1] * obj->pattern_len);
	if (obj->pattern_num == 4)
		return (blend_colors(obj->color, mapped_uv[2], obj->color2,
				1 - fabs(mapped_uv[2])));
	mapped_uv[2] = sin(mapped_uv[0] * obj->pattern_len)
		* cos(mapped_uv[1] * obj->pattern_len) / 2;
	return (blend_colors(obj->color, mapped_uv[2], obj->color2,
			1 - fabs(mapped_uv[2])));
}

void	initialize_pattern_basis(t_rt *rt, t_obj *obj)
{
	obj->ey = make_vector(0, 1, 0);
	if (obj->id == id_plane)
		obj->ey = obj->object.plane.orient;
	if (obj->id == id_cylinder)
	{
		obj->ey = obj->object.cylinder.orient;
		obj->h = obj->object.cylinder.height;
	}
	if (obj->id == id_cone)
	{
		obj->ey = obj->object.cone.orient;
		obj->h = obj->object.cone.h + obj->object.cone.h2;
	}
	obj->ex = cross_product(obj->ey, rt->camera.orient);
	obj->ez = cross_product(obj->ex, obj->ey);
	normalize_vector(&obj->ex);
	normalize_vector(&obj->ey);
	normalize_vector(&obj->ez);
}

t_color	resolve_pattern_color(t_obj *obj, t_vect phit)
{
	float	mapped_uv[3];

	ft_bzero(mapped_uv, sizeof(float) * 3);
	if (obj->pattern_num == 0)
		return (obj->color);
	map_pattern_uv(obj, phit, mapped_uv);
	return (resolve_basic_pattern(obj, mapped_uv));
}
