/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_modifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:20:00 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_modifier_basic(t_rt *rt, t_obj *obj, char **params, int i)
{
	if (ft_strncmp(params[i], "spc", 3) == 0
		&& parse_specular_modifier(params[i] + 4, obj))
		return (report_parsing_error(rt, params, ERR_INVALID_SPEC_PARAMS));
	if (ft_strncmp(params[i], "mir", 3) == 0
		&& parse_float_value(params[i] + 4, &obj->mirror))
		return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
	if (ft_strncmp(params[i], "ref", 3) == 0
		&& parse_float_value(params[i] + 4, &obj->refract))
		return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
	return (0);
}

static int	parse_modifier_material(t_rt *rt, t_obj *obj, char **params, int i)
{
	if (ft_strncmp(params[i], "pat", 3) == 0
		&& parse_pattern_modifier(params[i] + 4, obj))
		return (report_parsing_error(rt, params, ERR_INVALID_PATTERN_PARAMS));
	if (ft_strncmp(params[i], "bum", 3) == 0
		&& parse_bump_modifier(params[i] + 4, obj))
		return (report_parsing_error(rt, params, ERR_INVALID_BUMP_PARAMS));
	if (ft_strncmp(params[i], "txm", 3) == 0
		&& parse_texture_modifier(params[i] + 4, obj))
		return (report_parsing_error(rt, params, ERR_INVALID_TEXTURE_PARAMS));
	if (ft_strncmp(params[i], "alp", 3) == 0
		&& parse_float_value(params[i] + 4, &obj->alpha))
		return (report_parsing_error(rt, params, ERR_NOT_A_FLOAT));
	return (0);
}

int	parse_object_modifiers(t_rt *rt, t_obj *obj, char **params, int i)
{
	while (params && params[++i])
	{
		rt->pnum = i;
		if (parse_modifier_basic(rt, obj, params, i))
			return (1);
		if (parse_modifier_material(rt, obj, params, i))
			return (1);
	}
	return (0);
}
