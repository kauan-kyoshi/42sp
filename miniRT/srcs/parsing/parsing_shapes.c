/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_shapes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:28:47 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_orientation_component_invalid(t_vect orient)
{
	if (orient.x < -1.0f || orient.x > 1.0f)
		return (1);
	if (orient.y < -1.0f || orient.y > 1.0f)
		return (1);
	if (orient.z < -1.0f || orient.z > 1.0f)
		return (1);
	if (orient.x == 0.0f && orient.y == 0.0f && orient.z == 0.0f)
		return (1);
	return (0);
}

static int	parse_cylinder_param(t_rt *rt, t_obj *obj, char **params,
		t_cylinder *cylinder)
{
	int	i;

	i = rt->pnum;
	if (i == 1 && parse_vector3(params[i], &obj->coords))
		return (report_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
	if (i == 2 && parse_vector3(params[i], &cylinder->orient))
		return (report_parsing_error(rt, params, ERR_INVALID_NB_ORIENT));
	if (i == 2 && is_orientation_component_invalid(cylinder->orient))
		return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
	if (i == 3 && parse_float_value(params[i], &cylinder->diameter))
		return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
	if (i == 3 && cylinder->diameter <= 0.0f)
		return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
	if (i == 4 && parse_float_value(params[i], &cylinder->height))
		return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
	if (i == 4 && cylinder->height <= 0.0f)
		return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
	if (i == 5 && parse_dual_color(params[i], &obj->color, &obj->color2))
		return (report_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	return (0);
}

int	parse_plane_object(t_rt *rt, char **params, t_obj *obj)
{
	int		i;
	t_plane	plane;

	i = 0;
	ft_bzero(&plane, sizeof(t_plane));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector3(params[i], &obj->coords))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 2 && parse_vector3(params[i], &plane.orient))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_ORIENT));
		if (i == 2 && is_orientation_component_invalid(plane.orient))
			return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
		if (i == 3 && parse_dual_color(params[i], &obj->color, &obj->color2))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}
	normalize_vector(&plane.orient);
	plane.coords = obj->coords;
	obj->object.plane = plane;
	return (0);
}

int	parse_sphere_object(t_rt *rt, char **params, t_obj *obj)
{
	int			i;
	t_sphere	sphere;

	i = 0;
	ft_bzero(&sphere, sizeof(t_sphere));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector3(params[i], &obj->coords))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 2 && parse_float_value(params[i], &sphere.diameter))
			return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 2 && sphere.diameter <= 0.0f)
			return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
		if (i == 3 && parse_dual_color(params[i], &obj->color, &obj->color2))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}
	sphere.coords = obj->coords;
	obj->object.sphere = sphere;
	return (0);
}

int	parse_cylinder_object(t_rt *rt, char **params, t_obj *obj)
{
	int			i;
	t_cylinder	cylinder;

	i = 0;
	ft_bzero(&cylinder, sizeof(t_cylinder));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (parse_cylinder_param(rt, obj, params, &cylinder))
			return (1);
	}	
	normalize_vector(&cylinder.orient);
	cylinder.coords = obj->coords;
	obj->object.cylinder = cylinder;
	return (0);
}
