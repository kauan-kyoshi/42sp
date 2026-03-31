/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:29:44 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	intersect_cylinder_caps(t_ray *ray,
		t_cylinder *cylinder, t_hit *hit)
{
	t_plane	cap_plane;
	t_vect	cap_center[2];
	t_hit	candidate_hit;
	int		cap_idx;

	cap_center[0] = cylinder->p1;
	cap_center[1] = cylinder->p2;
	cap_plane.orient = cylinder->orient;
	cap_idx = -1;
	while (++cap_idx < 2)
	{
		cap_plane.coords = cap_center[cap_idx];
		if (intersect_plane(ray, &cap_plane, &candidate_hit)
			&& point_distance(candidate_hit.phit, cap_center[cap_idx])
			<= cylinder->diameter * 0.5 && hit->t > candidate_hit.t)
			*hit = candidate_hit;
	}
}

t_bool	intersect_sphere(t_ray *ray, t_sphere *sphere, t_hit *hit)
{
	t_vect	origin_to_center;
	float	projection_len;
	float	center_dist_sq;
	float	half_chord;
	float	far_hit_t;

	origin_to_center = vector_subtract(ray->or, sphere->coords);
	projection_len = dot_product(origin_to_center, ray->dir);
	if (projection_len < 0)
		return (FALSE);
	center_dist_sq = dot_product(origin_to_center, origin_to_center)
		- projection_len * projection_len;
	if (center_dist_sq > sphere->r2)
		return (FALSE);
	half_chord = sqrt(sphere->r2 - center_dist_sq);
	hit->t = projection_len - half_chord;
	far_hit_t = projection_len + half_chord;
	if (hit->t < EPSILON && far_hit_t < EPSILON)
		return (FALSE);
	if (hit->t < EPSILON || far_hit_t < hit->t)
		hit->t = far_hit_t;
	point_at_ray_distance(&hit->phit, ray, hit->t);
	hit->nhit = vector_subtract(sphere->coords, hit->phit);
	normalize_vector(&hit->nhit);
	return (TRUE);
}

t_bool	intersect_plane(t_ray *ray, t_plane *plane, t_hit *hit)
{
	float	ray_normal_dot;
	t_vect	ray_to_plane;

	ray_normal_dot = dot_product(plane->orient, ray->dir);
	if (ray_normal_dot == 0)
		return (FALSE);
	ray_to_plane = vector_subtract(ray->or, plane->coords);
	hit->t = dot_product(ray_to_plane, plane->orient) / ray_normal_dot;
	if (hit->t < EPSILON)
		return (FALSE);
	point_at_ray_distance(&hit->phit, ray, hit->t);
	hit->nhit = plane->orient;
	if (dot_product(hit->nhit, ray->dir) > 0)
		hit->nhit = vector_negate(hit->nhit);
	return (TRUE);
}

t_bool	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, t_hit *hit)
{
	t_hit	candidate_hit;

	hit->t = INFINITY;
	intersect_cylinder_caps(ray, cylinder, hit);
	if (intersect_infinite_cylinder(ray, cylinder, &candidate_hit)
		&& pow(point_distance(cylinder->coords, candidate_hit.phit), 2)
		<= pow(cylinder->height * 0.5, 2) + cylinder->r2
		&& hit->t > candidate_hit.t)
		*hit = candidate_hit;
	return (hit->t < INFINITY && hit->t > EPSILON);
}
