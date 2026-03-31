/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder_body.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:20:00 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:25 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	choose_cylinder_hit_t(t_quadratic *quadratic)
{
	if (!solve_quadratic_equation(quadratic)
		|| (quadratic->t2 <= EPSILON && quadratic->t1 <= EPSILON))
		return (FALSE);
	if (quadratic->t1 <= EPSILON || (quadratic->t2 > EPSILON
			&& quadratic->t2 < quadratic->t1))
		quadratic->t1 = quadratic->t2;
	return (TRUE);
}

t_bool	intersect_infinite_cylinder(t_ray *ray,
		t_cylinder *cylinder, t_hit *hit)
{
	t_quadratic	quadratic;
	t_vect		ray_cross_axis;
	t_vect		origin_cross_axis;

	ray_cross_axis = cross_product(ray->dir, cylinder->orient);
	origin_cross_axis = vector_subtract(cylinder->coords, ray->or);
	origin_cross_axis = cross_product(origin_cross_axis, cylinder->orient);
	quadratic.a = dot_product(ray_cross_axis, ray_cross_axis);
	quadratic.b = 2 * dot_product(ray_cross_axis, origin_cross_axis);
	quadratic.c = dot_product(origin_cross_axis, origin_cross_axis)
		- cylinder->r2;
	if (!choose_cylinder_hit_t(&quadratic))
		return (FALSE);
	hit->t = quadratic.t1;
	point_at_ray_distance(&hit->phit, ray, hit->t);
	origin_cross_axis = vector_subtract(cylinder->coords, hit->phit);
	hit->nhit = cross_product(origin_cross_axis, cylinder->orient);
	hit->nhit = cross_product(hit->nhit, cylinder->orient);
	normalize_vector(&hit->nhit);
	if (dot_product(hit->nhit, ray->dir) > 0)
		hit->nhit = vector_negate(hit->nhit);
	return (TRUE);
}
