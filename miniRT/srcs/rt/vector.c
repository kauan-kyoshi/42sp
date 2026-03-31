/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:30:36 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:42:11 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	make_vector(float x_coord, float y_coord, float z_coord)
{
	t_vect	vector_value;

	vector_value.x = x_coord;
	vector_value.y = y_coord;
	vector_value.z = z_coord;
	return (vector_value);
}

float	vector_length(t_vect vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y
			+ vector.z * vector.z));
}

t_vect	vector_subtract(t_vect lhs, t_vect rhs)
{
	t_vect	result;

	result.x = rhs.x - lhs.x;
	result.y = rhs.y - lhs.y;
	result.z = rhs.z - lhs.z;
	return (result);
}

t_vect	vector_add(t_vect lhs, t_vect rhs)
{
	t_vect	result;

	result.x = rhs.x + lhs.x;
	result.y = rhs.y + lhs.y;
	result.z = rhs.z + lhs.z;
	return (result);
}

t_vect	vector_scale(t_vect vector, float scalar)
{
	t_vect	result;

	result.x = vector.x * scalar;
	result.y = vector.y * scalar;
	result.z = vector.z * scalar;
	return (result);
}
