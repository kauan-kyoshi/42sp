/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_shapes2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:20:00 by klima-do          #+#    #+#             */
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

static int	parse_cone_param(t_rt *rt, t_obj *obj, char **params,
		t_cone *cone)
{
	int	i;

	i = rt->pnum;
	if (i == 1 && parse_vector3(params[i], &obj->coords))
		return (report_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
	if (i == 2 && parse_vector3(params[i], &cone->orient))
		return (report_parsing_error(rt, params, ERR_INVALID_NB_ORIENT));
	if (i == 2 && is_orientation_component_invalid(cone->orient))
		return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
	if (i == 3 && parse_float_value(params[i], &cone->h))
		return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
	if (i == 4 && parse_float_value(params[i], &cone->h2))
		return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
	if (i == 5 && parse_float_value(params[i], &cone->angle))
		return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
	if (i == 6 && parse_dual_color(params[i], &obj->color, &obj->color2))
		return (report_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	return (0);
}

int	parse_cone_object(t_rt *rt, char **params, t_obj *obj)
{
	int		i;
	t_cone	cone;

	i = 0;
	ft_bzero(&cone, sizeof(t_cone));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (parse_cone_param(rt, obj, params, &cone))
			return (1);
	}
	normalize_vector(&cone.orient);
	cone.coords = obj->coords;
	obj->object.cone = cone;
	return (0);
}

int	parse_triangle_object(t_rt *rt, char **params, t_obj *obj)
{
	int			i;
	t_triangle	triangle;

	i = 0;
	ft_bzero(&triangle, sizeof(t_triangle));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector3(params[i], &triangle.c[0]))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 2 && parse_vector3(params[i], &triangle.c[1]))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 3 && parse_vector3(params[i], &triangle.c[2]))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 4 && parse_dual_color(params[i], &obj->color, &obj->color2))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}
	triangle.color = obj->color;
	obj->object.triangle = triangle;
	return (0);
}

int	parse_torus_object(t_rt *rt, char **params, t_obj *obj)
{
	int		i;
	t_torus	torus;

	i = 0;
	ft_bzero(&torus, sizeof(t_torus));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector3(params[i], &obj->coords))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 2 && parse_vector3(params[i], &torus.orient))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_ORIENT));
		if (i == 2 && is_orientation_component_invalid(torus.orient))
			return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
		if (i == 3 && parse_float_value(params[i], &torus.sml_r))
			return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 4 && parse_float_value(params[i], &torus.big_r2))
			return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 5 && parse_dual_color(params[i], &obj->color, &obj->color2))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}
	normalize_vector(&torus.orient);
	torus.coords = obj->coords;
	obj->object.torus = torus;
	return (0);
}
