/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:29:54 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	compute_specular_light(t_rays *rays, t_light *light)
{
	t_vect	specular_dir;
	float	spec_angle;
	t_color	color;

	spec_angle = dot_product(rays->shadowray.dir, rays->hit.nhit);
	specular_dir = vector_scale(rays->hit.nhit, spec_angle * 2);
	specular_dir = vector_subtract(specular_dir, rays->shadowray.dir);
	spec_angle = dot_product(specular_dir, rays->prime_ray.dir);
	if (spec_angle > EPSILON)
		spec_angle = pow(spec_angle, rays->closest_obj->specn)
			* rays->closest_obj->speckv;
	color = make_color(1, 1, 1);
	color = apply_light_contribution(color, color,
			light->brightness * spec_angle);
	return (color);
}

t_color	compute_diffuse_light(t_rays *rays, t_light *light)
{
	t_color	color;
	float	diffuse_angle;

	color = rays->hit.color;
	diffuse_angle = dot_product(rays->shadowray.dir, rays->hit.nhit);
	color = apply_light_contribution(color, light->color,
			light->brightness * diffuse_angle);
	return (color);
}

t_bool	is_shadowed(t_rt *rt, t_rays *rays, t_light *light)
{
	rays->shadowray.or = rays->hit.phit;
	rays->shadowray.dir = vector_subtract(rays->hit.phit, light->coords);
	normalize_vector(&rays->shadowray.dir);
	point_at_ray_distance(&rays->shadowray.or, &rays->shadowray, 0.01);
	return (find_closest_object_hit(&rays->shadowray,
			rt->objs, &rays->shadow_hit)
		&& point_distance(rays->shadowray.or, light->coords)
		> point_distance(rays->shadow_hit.phit, rays->shadowray.or));
}

t_color	trace_refraction(t_rt *rt, t_rays *rays, int max_reflect)
{
	float	eta;

	eta = 1 / rays->closest_obj->refract;
	rays->prime_ray.or = rays->hit.phit;
	rays->prime_ray.dir = refract_vector(rays->prime_ray.dir, rays->hit.nhit,
			eta);
	point_at_ray_distance(&rays->prime_ray.or, &rays->prime_ray, EPSILON);
	intersect_object(&rays->prime_ray, rays->closest_obj, &rays->hit);
	rays->prime_ray.or = rays->hit.phit;
	rays->hit.nhit = vector_negate(rays->hit.nhit);
	rays->prime_ray.dir = refract_vector(rays->prime_ray.dir, rays->hit.nhit,
			eta);
	return (trace_ray(rt, rays, max_reflect));
}

t_color	trace_reflection(t_rt *rt, t_rays *rays, int max_reflect)
{
	t_rays		reflected_rays;

	reflected_rays.prime_ray.or = rays->hit.phit;
	reflected_rays.prime_ray.dir = reflect_vector(rays->prime_ray.dir,
			rays->hit.nhit);
	normalize_vector(&reflected_rays.prime_ray.dir);
	return (trace_ray(rt, &reflected_rays, max_reflect));
}
