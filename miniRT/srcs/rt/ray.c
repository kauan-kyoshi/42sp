/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:30:15 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:42:11 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	initialize_ray(t_ray *ray, t_vect *origin, t_vect *direction)
{
	ray->or.x = origin->x;
	ray->or.y = origin->y;
	ray->or.z = origin->z;
	ray->dir.x = direction->x;
	ray->dir.y = direction->y;
	ray->dir.z = direction->z;
	normalize_vector(&ray->dir);
}

void	build_camera_basis(t_rt *rt)
{
	t_vect	forward;
	t_vect	right;
	t_vect	up;
	t_vect	tmp;

	tmp = make_vector(0, 1, 0);
	forward = rt->camera.orient;
	normalize_vector(&forward);
	right = cross_product(tmp, forward);
	up = cross_product(forward, right);
	rt->cam_matrix[0][0] = right.x;
	rt->cam_matrix[0][1] = right.y;
	rt->cam_matrix[0][2] = right.z;
	rt->cam_matrix[1][0] = up.x;
	rt->cam_matrix[1][1] = up.y;
	rt->cam_matrix[1][2] = up.z;
	rt->cam_matrix[2][0] = forward.x;
	rt->cam_matrix[2][1] = forward.y;
	rt->cam_matrix[2][2] = forward.z;
}

t_vect	transform_camera_to_world(float matrix[4][4], t_vect *vector)
{
	t_vect	world_space_vector;

	world_space_vector.x = vector->x * matrix[0][0]
		+ vector->y * matrix[1][0] + vector->z * matrix[2][0];
	world_space_vector.y = vector->x * matrix[0][1]
		+ vector->y * matrix[1][1] + vector->z * matrix[2][1];
	world_space_vector.z = vector->x * matrix[0][2]
		+ vector->y * matrix[1][2] + vector->z * matrix[2][2];
	return (world_space_vector);
}

void	build_camera_ray(t_rt *rt, t_ray *ray, float pixel_x, float pixel_y)
{
	t_camera	*camera;

	camera = &rt->camera;
	ray->or = make_vector(camera->coords.x, camera->coords.y, camera->coords.z);
	ray->dir.x = (2.0 * (pixel_x + 0.5) / (float) rt->width - 1.0)
		* camera->scale * rt->aspectratio;
	ray->dir.y = (1.0 - 2.0 * (pixel_y + 0.5) / (float) rt->height)
		* camera->scale;
	ray->dir.z = FOCAL_DIST;
	ray->dir = transform_camera_to_world(rt->cam_matrix, &ray->dir);
	normalize_vector(&ray->dir);
}

t_vect	*point_at_ray_distance(t_vect *point, t_ray *ray, float distance)
{
	point->x = ray->or.x + distance * ray->dir.x;
	point->y = ray->or.y + distance * ray->dir.y;
	point->z = ray->or.z + distance * ray->dir.z;
	return (point);
}
