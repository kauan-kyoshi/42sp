/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:30:30 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*find_closest_object_hit(t_ray *ray, t_obj *obj, t_hit *hit)
{
	float	closest_t;
	t_obj	*closest_obj;
	t_hit	candidate_hit;

	closest_obj = NULL;
	closest_t = INFINITY;
	while (obj)
	{
		if (intersect_object(ray, obj, &candidate_hit))
		{
			if (candidate_hit.t < closest_t)
			{
				closest_obj = obj;
				closest_t = candidate_hit.t;
				*hit = candidate_hit;
			}
		}
		obj = obj->next;
	}
	if (closest_obj)
		hit->color = resolve_object_color(closest_obj, hit);
	return (closest_obj);
}

static t_color	compose_lighting_color(t_obj *obj, t_colors *colors)
{
	t_color	final_color;

	final_color.r = colors->ambient.r + colors->diffuse.r + colors->specular.r;
	final_color.g = colors->ambient.g + colors->diffuse.g + colors->specular.g;
	final_color.b = colors->ambient.b + colors->diffuse.b + colors->specular.b;
	if (obj && obj->mirror > 0)
		final_color = blend_colors(final_color, 1 - obj->mirror,
				colors->reflect, obj->mirror);
	if (obj && obj->refract > 0)
		final_color = blend_colors(colors->refract, 0.7, final_color, 0.3);
	if (final_color.r > 1)
		final_color.r = 1;
	if (final_color.g > 1)
		final_color.g = 1;
	if (final_color.b > 1)
		final_color.b = 1;
	return (final_color);
}

static void	accumulate_lighting(t_rt *rt, t_rays *r, t_colors *colors)
{
	t_light	*light;

	colors->ambient = r->hit.color;
	colors->ambient = apply_light_contribution(colors->ambient,
			rt->ambient.color, rt->ambient.lighting);
	light = rt->light;
	while (light)
	{
		colors->is_shadow = is_shadowed(rt, r, light);
		if (!colors->is_shadow)
			colors->diffuse = blend_colors(colors->diffuse, 1,
					compute_diffuse_light(r, light), 1);
		if (!colors->is_shadow)
			colors->specular = blend_colors(colors->specular, 1,
					compute_specular_light(r, light), 1);
		light = light->next;
	}
}

t_color	trace_ray(t_rt *rt, t_rays *r, int max_reflect)
{
	t_colors	colors;
	t_obj		*shaded_obj;

	ft_memset(&colors, 0, sizeof(colors));
	r->closest_obj = find_closest_object_hit(&r->prime_ray, rt->objs, &r->hit);
	shaded_obj = r->closest_obj;
	if (!r->closest_obj)
		return (make_color(0, 0, 0));
	if (r->closest_obj->has_bump)
		apply_bump_map(r->closest_obj, &r->closest_obj->bump, &r->hit);
	accumulate_lighting(rt, r, &colors);
	--max_reflect;
	if (r->closest_obj->mirror > 0 && max_reflect > 0)
		colors.reflect = trace_reflection(rt, r, max_reflect);
	if (r->closest_obj->refract > 0 && max_reflect > 0)
		colors.refract = trace_refraction(rt, r, max_reflect);
	if (max_reflect < 0)
		shaded_obj = NULL;
	return (compose_lighting_color(shaded_obj, &colors));
}
