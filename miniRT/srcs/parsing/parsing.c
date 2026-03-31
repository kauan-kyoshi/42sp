/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:29:08 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_scene_line(t_rt *rt, char *line)
{
	if (ft_strncmp(line, "R", 1) == 0 && (line[1] == ' ' || !line[1]))
		return (parse_resolution_settings(rt, line));
	if (ft_strncmp(line, "A", 1) == 0 && (line[1] == ' ' || !line[1]))
		return (parse_ambient_light(rt, line));
	if (ft_strncmp(line, "C", 1) == 0 && (line[1] == ' ' || !line[1]))
		return (parse_camera_definition(rt, line, 0));
	if (ft_strncmp(line, "L", 1) == 0 && (line[1] == ' ' || !line[1]))
		return (parse_point_light(rt, line));
	if (ft_strncmp(line, "sp", 2) == 0 && (line[2] == ' ' || !line[2]))
		return (parse_object_definition(rt, line, id_sphere, NB_PARAMS_SPHERE));
	if (ft_strncmp(line, "pl", 2) == 0 && (line[2] == ' ' || !line[2]))
		return (parse_object_definition(rt, line, id_plane, NB_PARAMS_PLANE));
	if (ft_strncmp(line, "cy", 2) == 0 && (line[2] == ' ' || !line[2]))
		return (parse_object_definition(rt, line, id_cylinder,
				NB_PARAMS_CYLINDER));
	if (ft_strncmp(line, "co", 2) == 0 && (line[2] == ' ' || !line[2]))
		return (parse_object_definition(rt, line, id_cone, NB_PARAMS_CONE));
	if (ft_strncmp(line, "tr", 2) == 0 && (line[2] == ' ' || !line[2]))
		return (parse_object_definition(rt, line, id_triangle,
				NB_PARAMS_TRIANGLE));
	if (ft_strncmp(line, "to", 2) == 0 && (line[2] == ' ' || !line[2]))
		return (parse_object_definition(rt, line, id_torus, NB_PARAMS_TORUS));
	return (report_parsing_error(rt, NULL, ERR_INVALID_IDENTIFIER));
}

int	parse_object_definition(t_rt *rt, char *line, t_obj_id id, int nb_params)
{
	t_obj	*obj;
	char	**params;

	params = ft_split(line, ' ');
	if (string_array_length(params) < nb_params)
		return (report_parsing_error(rt, params, ERR_INVALID_NB_PARAMS));
	obj = alloc_object(rt, id);
	if (id == id_plane && parse_plane_object(rt, params, obj))
		return (1);
	if (id == id_sphere && parse_sphere_object(rt, params, obj))
		return (1);
	if (id == id_cylinder && parse_cylinder_object(rt, params, obj))
		return (1);
	if (id == id_cone && parse_cone_object(rt, params, obj))
		return (1);
	if (id == id_triangle && parse_triangle_object(rt, params, obj))
		return (1);
	if (string_array_length(params) > nb_params
		&& parse_object_modifiers(rt, obj, params, nb_params - 1))
		return (1);
	free_string_array(params);
	return (0);
}
