/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:30:42 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:42:11 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	dot_product(t_vect lhs, t_vect rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

t_vect	cross_product(t_vect lhs, t_vect rhs)
{
	t_vect	result;

	result.x = lhs.y * rhs.z - lhs.z * rhs.y;
	result.y = lhs.z * rhs.x - lhs.x * rhs.z;
	result.z = lhs.x * rhs.y - lhs.y * rhs.x;
	return (result);
}

float	point_distance(t_vect point_a, t_vect point_b)
{
	float	dx;
	float	dy;
	float	dz;

	dx = point_a.x - point_b.x;
	dy = point_a.y - point_b.y;
	dz = point_a.z - point_b.z;
	dx = pow(dx, 2);
	dy = pow(dy, 2);
	dz = pow(dz, 2);
	return (sqrt(dx + dy + dz));
}

t_vect	vector_negate(t_vect vector)
{
	vector.x = -vector.x;
	vector.y = -vector.y;
	vector.z = -vector.z;
	return (vector);
}

t_vect	*normalize_vector(t_vect *vector)
{
	float	inv_length;

	inv_length = 1 / vector_length(*vector);
	vector->x *= inv_length;
	vector->y *= inv_length;
	vector->z *= inv_length;
	return (vector);
}
