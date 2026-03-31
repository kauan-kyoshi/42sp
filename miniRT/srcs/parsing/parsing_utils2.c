/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:29:00 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:16:31 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_invalid_xpm_path(char *path)
{
	int	fd;
	int	len;

	len = ft_strlen(path) - 4;
	if (len < 5 || ft_strncmp(path + len, ".xpm", 4) != 0)
		return (1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	parse_bump_modifier(char *param, t_obj *obj)
{
	char	**params;

	params = ft_split(param, ',');
	if (string_array_length(params) == 2
		&& parse_float_value(params[1], &obj->bump_f))
		return (1);
	if (is_invalid_xpm_path(params[0]))
		return (1);
	obj->bump.path = params[0];
	obj->has_bump = TRUE;
	return (0);
}

int	parse_texture_modifier(char *param, t_obj *obj)
{
	char	**params;

	params = ft_split(param, ',');
	if (string_array_length(params) == 2
		&& parse_float_value(params[1], &obj->texture_f))
		return (1);
	if (is_invalid_xpm_path(params[0]))
		return (1);
	obj->texture.path = params[0];
	obj->has_texture = TRUE;
	return (0);
}

int	parse_specular_modifier(char *str, t_obj *obj)
{
	int		i;
	int		ret;
	char	**params;

	i = -1;
	ret = 0;
	params = ft_split(str, ',');
	while (params && params[++i])
		if (!is_valid_float_literal(params[i]))
			ret = 1;
	if (string_array_length(params) != 2)
		ret = 1;
	else
	{
		obj->speckv = parse_float_literal(params[0]);
		obj->specn = parse_float_literal(params[1]);
	}
	free_string_array(params);
	return (ret);
}

int	parse_pattern_modifier(char *str, t_obj *obj)
{
	int		ret;
	char	**params;

	ret = 0;
	params = ft_split(str, ',');
	if (string_array_length(params) != 2)
		ret = 1;
	if (!is_valid_float_literal(params[0]))
		ret = 1;
	if (!is_valid_unsigned_number(params[1]))
		ret = 1;
	if (!ret)
	{
		obj->pattern_len = parse_float_literal(params[0]);
		obj->pattern_num = ft_atoi(params[1]);
	}
	free_string_array(params);
	return (ret);
}
