/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:28:32 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_camera_param(t_rt *rt, char **params, t_camera *camera, int i)
{
	if (i == 1 && parse_vector3(params[i], &camera->coords))
		return (report_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
	if (i == 2 && parse_vector3(params[i], &camera->orient))
		return (report_parsing_error(rt, params, ERR_INVALID_NB_ORIENT));
	if (i == 2 && (camera->orient.x < -1.0f || camera->orient.x > 1.0f
			|| camera->orient.y < -1.0f || camera->orient.y > 1.0f
			|| camera->orient.z < -1.0f || camera->orient.z > 1.0f
			|| (camera->orient.x == 0.0f && camera->orient.y == 0.0f
				&& camera->orient.z == 0.0f)))
		return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
	if (i == 3 && parse_size_value(params[i], &camera->fov))
		return (report_parsing_error(rt, params, ERR_NOT_A_ULONG));
	if (i == 3 && camera->fov > 180)
		return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
	return (0);
}

int	parse_camera_definition(t_rt *rt, char *line, int i)
{
	char		**params;
	t_camera	camera;

	params = ft_split(line, ' ');
	if (rt->camera.id)
		return (report_parsing_error(rt, params, ERR_TOO_MANY_CAMERAS));
	if (string_array_length(params) != 4)
		return (report_parsing_error(rt, params, ERR_INVALID_NB_PARAMS));
	ft_bzero(&camera, sizeof(t_camera));
	camera.id = id_camera;
	while (params && params[++i])
	{
		rt->pnum = i;
		if (parse_camera_param(rt, params, &camera, i))
			return (1);
	}
	normalize_vector(&camera.orient);
	rt->camera = camera;
	free_string_array(params);
	return (0);
}

int	parse_ambient_light(t_rt *rt, char *line)
{
	int			i;
	char		**params;
	t_ambient	ambient;

	i = 0;
	params = ft_split(line, ' ');
	if (rt->ambient.id)
		return (report_parsing_error(rt, params, ERR_TOO_MANY_AMBIENTS));
	if (string_array_length(params) != 3)
		return (report_parsing_error(rt, params, ERR_INVALID_NB_PARAMS));
	ft_bzero(&ambient, sizeof(t_ambient));
	ambient.id = id_ambient;
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_float_value(params[i], &ambient.lighting))
			return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 1 && (ambient.lighting < 0.0f || ambient.lighting > 1.0f))
			return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
		if (i == 2 && parse_rgb_color(params[i], &ambient.color))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}
	rt->ambient = ambient;
	free_string_array(params);
	return (0);
}

int	parse_point_light(t_rt *rt, char *line)
{
	int		i;
	char	**params;
	t_light	*light;

	i = 0;
	params = ft_split(line, ' ');
	if (string_array_length(params) != 4)
		return (report_parsing_error(rt, params, ERR_INVALID_NB_PARAMS));
	light = alloc_light(rt);
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector3(params[i], &light->coords))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COORDS));
		if (i == 2 && parse_float_value(params[i], &light->brightness))
			return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 2 && (light->brightness < 0.0f || light->brightness > 1.0f))
			return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
		if (i == 3 && parse_rgb_color(params[i], &light->color))
			return (report_parsing_error(rt, params, ERR_INVALID_NB_COLORS));
	}
	free_string_array(params);
	return (0);
}

int	parse_resolution_settings(t_rt *rt, char *line)
{
	int		i;
	char	**params;

	i = 0;
	params = ft_split(line, ' ');
	if (string_array_length(params) != 3)
		return (report_parsing_error(rt, params, ERR_INVALID_NB_PARAMS));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_float_value(params[i], &rt->width))
			return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 1 && rt->width <= 0.0f)
			return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
		if (i == 2 && parse_float_value(params[i], &rt->height))
			return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
		if (i == 2 && rt->height <= 0.0f)
			return (report_parsing_error(rt, params, ERR_OUT_OF_RANGE));
	}
	free_string_array(params);
	return (0);
}
