/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:30:47 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:42:11 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	reflect_vector(t_vect incident, t_vect normal)
{
	t_vect	reflected;

	reflected = vector_scale(normal, 2 * dot_product(incident, normal));
	reflected = vector_subtract(reflected, incident);
	return (reflected);
}

t_vect	refract_vector(t_vect incident, t_vect normal, float eta)
{
	float	cos_in;
	float	cos_out;
	t_vect	refracted;

	cos_in = dot_product(incident, normal);
	cos_out = sqrt(1 - eta * eta * (1 - cos_in * cos_in));
	refracted = vector_scale(normal, eta * cos_in - cos_out);
	refracted = vector_add(refracted, vector_scale(incident, eta));
	normalize_vector(&refracted);
	return (refracted);
}
