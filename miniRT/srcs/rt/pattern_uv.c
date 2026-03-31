/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_uv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:20:00 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	map_sphere_uv(t_obj *obj, t_vect hit_point, float *uv)
{
	t_vect	normalized_dir;
	float	u_axis_dot;
	float	v_axis_dot;
	float	w_axis_dot;

	normalized_dir = vector_subtract(obj->coords, hit_point);
	normalize_vector(&normalized_dir);
	u_axis_dot = dot_product(obj->ex, normalized_dir);
	v_axis_dot = dot_product(obj->ey, normalized_dir);
	w_axis_dot = dot_product(obj->ez, normalized_dir);
	uv[0] = atan2(u_axis_dot, w_axis_dot) / (2 * M_PI) + 0.5;
	uv[1] = v_axis_dot * 0.5 + 0.5;
}

void	map_plane_uv(t_obj *obj, t_vect hit_point, float *uv)
{
	t_vect	hit_offset;

	hit_offset = vector_subtract(hit_point, obj->coords);
	uv[0] = dot_product(hit_offset, obj->ex);
	uv[1] = dot_product(hit_offset, obj->ez);
}

void	map_cylindrical_uv(t_obj *obj, t_vect hit_point, float *uv)
{
	t_vect	normalized_dir;
	float	height_proj;
	float	u_axis_dot;
	float	w_axis_dot;

	normalized_dir = vector_subtract(obj->coords, hit_point);
	height_proj = dot_product(obj->ey, normalized_dir);
	normalize_vector(&normalized_dir);
	u_axis_dot = dot_product(obj->ex, normalized_dir);
	w_axis_dot = dot_product(obj->ez, normalized_dir);
	uv[0] = atan2(u_axis_dot, w_axis_dot) / (2 * M_PI) + 0.5;
	uv[1] = height_proj / obj->h + 0.5;
}
