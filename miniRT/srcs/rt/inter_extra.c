/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:20:00 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	setup_cone_quadratic(t_quadratic *q, t_ray *ray,
		t_cone *cone, t_vect origin_to_cone)
{
	float	ray_axis_dot;
	float	origin_axis_dot;

	ray_axis_dot = dot_product(ray->dir, cone->orient);
	origin_axis_dot = dot_product(origin_to_cone, cone->orient);
	q->a = ray_axis_dot * ray_axis_dot - cone->cos2;
	q->b = 2 * (ray_axis_dot * origin_axis_dot
			- dot_product(ray->dir, origin_to_cone) * cone->cos2);
	q->c = origin_axis_dot * origin_axis_dot
		- dot_product(origin_to_cone, origin_to_cone) * cone->cos2;
}

static int	is_triangle_hit_inside(t_triangle *triangle, t_vect phit)
{
	t_vect	edge_cross;
	int		edge_index;

	edge_index = -1;
	while (++edge_index < 3)
	{
		edge_cross = cross_product(triangle->edge[edge_index],
				vector_subtract(triangle->c[edge_index], phit));
		if (dot_product(triangle->n, edge_cross) < 0)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	intersect_cone_body(t_ray *ray, t_cone *cone, t_hit *hit)
{
	t_quadratic	quadratic;
	t_vect		origin_to_cone;
	t_vect		hit_to_apex;

	origin_to_cone = vector_subtract(cone->coords, ray->or);
	setup_cone_quadratic(&quadratic, ray, cone, origin_to_cone);
	if (!solve_quadratic_equation(&quadratic)
		|| (quadratic.t2 <= EPSILON && quadratic.t1 <= EPSILON))
		return (FALSE);
	if (quadratic.t1 <= EPSILON || (quadratic.t2 > EPSILON
			&& quadratic.t2 < quadratic.t1))
		quadratic.t1 = quadratic.t2;
	hit->t = quadratic.t1;
	point_at_ray_distance(&hit->phit, ray, hit->t);
	hit_to_apex = vector_subtract(cone->coords, hit->phit);
	if (dot_product(cone->orient, hit_to_apex) > cone->h
		|| dot_product(cone->orient, hit_to_apex) < -cone->h2)
		return (FALSE);
	hit->nhit = cross_product(cross_product(hit_to_apex, cone->orient),
			hit_to_apex);
	normalize_vector(&hit->nhit);
	return (TRUE);
}

t_bool	intersect_cone(t_ray *ray, t_cone *cone, t_hit *hit)
{
	t_plane	cap_plane;
	t_hit	candidate_hit;

	hit->t = INFINITY;
	cap_plane.coords = cone->c1;
	cap_plane.orient = cone->orient;
	if (intersect_plane(ray, &cap_plane, &candidate_hit)
		&& point_distance(candidate_hit.phit, cone->c1) <= cone->r1
		&& hit->t > candidate_hit.t)
		*hit = candidate_hit;
	cap_plane.coords = cone->c2;
	if (intersect_plane(ray, &cap_plane, &candidate_hit)
		&& point_distance(candidate_hit.phit, cone->c2) <= cone->r2
		&& hit->t > candidate_hit.t)
		*hit = candidate_hit;
	if (intersect_cone_body(ray, cone, &candidate_hit)
		&& hit->t > candidate_hit.t)
		*hit = candidate_hit;
	if (dot_product(hit->nhit, ray->dir) > 0)
		hit->nhit = vector_negate(hit->nhit);
	return (hit->t < INFINITY && hit->t > EPSILON);
}

t_bool	intersect_triangle(t_ray *ray, t_triangle *triangle, t_hit *hit)
{
	float	normal_ray_dot;
	float	plane_offset;

	normal_ray_dot = dot_product(triangle->n, ray->dir);
	if (fabs(normal_ray_dot) < EPSILON)
		return (FALSE);
	plane_offset = -dot_product(triangle->n, triangle->c[0]);
	hit->t = -(dot_product(ray->or, triangle->n) + plane_offset)
		/ normal_ray_dot;
	if (hit->t < EPSILON)
		return (FALSE);
	point_at_ray_distance(&hit->phit, ray, hit->t);
	if (!is_triangle_hit_inside(triangle, hit->phit))
		return (FALSE);
	hit->nhit = triangle->n;
	if (dot_product(hit->nhit, ray->dir) > 0)
		hit->nhit = vector_negate(hit->nhit);
	return (TRUE);
}
