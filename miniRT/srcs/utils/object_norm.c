/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:32:47 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:42:11 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	normalize_triangle(t_rt *rt, t_triangle *triangle)
{
	t_vect	v;
	t_vect	tmp;

	triangle->edge[0] = vector_subtract(triangle->c[0], triangle->c[1]);
	triangle->edge[1] = vector_subtract(triangle->c[1], triangle->c[2]);
	triangle->edge[2] = vector_subtract(triangle->c[2], triangle->c[0]);
	triangle->n = cross_product(triangle->edge[0], triangle->edge[1]);
	triangle->area2 = vector_length(triangle->n);
	normalize_vector(&triangle->n);
	v = vector_subtract(rt->camera.orient, triangle->c[0]);
	if (dot_product(v, triangle->n) > 0)
	{
		tmp = triangle->c[1];
		triangle->c[1] = triangle->c[2];
		triangle->c[2] = tmp;
		normalize_triangle(rt, triangle);
	}
}

void	normalize_cone(t_cone *cone)
{
	normalize_vector(&cone->orient);
	cone->cos2 = pow(cos(cone->angle), 2);
	cone->c1 = vector_scale(cone->orient, cone->h);
	cone->c1 = vector_add(cone->c1, cone->coords);
	cone->c2 = vector_scale(cone->orient, -cone->h2);
	cone->c2 = vector_add(cone->c2, cone->coords);
	cone->r1 = tan(cone->angle) * cone->h;
	cone->r2 = tan(cone->angle) * cone->h2;
}

void	normalize_cylinder(t_cylinder *cylinder)
{
	normalize_vector(&cylinder->orient);
	cylinder->r2 = cylinder->diameter * cylinder->diameter * 0.25;
	cylinder->delta_p = vector_scale(cylinder->orient, cylinder->height);
	cylinder->p1 = vector_scale(cylinder->orient, -0.5 * cylinder->height);
	cylinder->p1 = vector_add(cylinder->p1, cylinder->coords);
	cylinder->p2 = vector_scale(cylinder->orient, 0.5 * cylinder->height);
	cylinder->p2 = vector_add(cylinder->p2, cylinder->coords);
}

void	load_object_maps(t_rt *rt, t_obj *obj)
{
	if (obj->has_texture && !obj->texture.img)
	{
		obj->texture.img = mlx_xpm_file_to_image(rt->mlx, obj->texture.path,
				&obj->texture.width, &obj->texture.height);
		if (!obj->texture.img)
			obj->has_texture = FALSE;
		else
			obj->texture.addr = mlx_get_data_addr(obj->texture.img,
					&obj->texture.bits_per_pixel, &obj->texture.line_length,
					&obj->texture.endian);
	}
	if (obj->has_bump && !obj->bump.img)
	{
		obj->bump.img = mlx_xpm_file_to_image(rt->mlx,
				obj->bump.path, &obj->bump.width, &obj->bump.height);
		if (!obj->bump.img)
			obj->has_bump = FALSE;
		else
			obj->bump.addr = mlx_get_data_addr(obj->bump.img,
					&obj->bump.bits_per_pixel, &obj->bump.line_length,
					&obj->bump.endian);
	}
}

void	normalize_scene_objects(t_rt *rt)
{
	t_obj		*objs;
	t_camera	*cam;

	cam = &rt->camera;
	cam->scale = tan(cam->fov / 2 * M_PI / 180);
	rt->aspectratio = (float) rt->width / rt->height;
	rt->img.addr_incr = rt->img.bits_per_pixel / 8;
	rt->bg_color = unpack_rgb_color(0x424242);
	build_camera_basis(rt);
	objs = rt->objs;
	while (objs)
	{
		load_object_maps(rt, objs);
		if (objs->id == id_sphere)
			objs->object.sphere.r2 = pow(objs->object.sphere.diameter / 2, 2);
		if (objs->id == id_cone)
			normalize_cone(&objs->object.cone);
		if (objs->id == id_triangle)
			normalize_triangle(rt, &objs->object.triangle);
		if (objs->id == id_cylinder)
			normalize_cylinder(&objs->object.cylinder);
		initialize_pattern_basis(rt, objs);
		objs = objs->next;
	}
}
