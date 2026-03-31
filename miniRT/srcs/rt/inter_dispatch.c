/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_dispatch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:20:00 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:25 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_object(t_ray *ray, t_obj *obj, t_hit *hit)
{
	if (obj->id == id_sphere)
		return (intersect_sphere(ray, &obj->object.sphere, hit));
	if (obj->id == id_plane)
		return (intersect_plane(ray, &obj->object.plane, hit));
	if (obj->id == id_cylinder)
		return (intersect_cylinder(ray, &obj->object.cylinder, hit));
	if (obj->id == id_cone)
		return (intersect_cone(ray, &obj->object.cone, hit));
	if (obj->id == id_triangle)
		return (intersect_triangle(ray, &obj->object.triangle, hit));
	if (obj->id == id_torus)
		return (intersect_torus(ray, &obj->object.torus, hit));
	return (FALSE);
}
