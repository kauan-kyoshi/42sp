/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:28:51 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_rgb_triplet(char **rgb, t_color *color)
{
	int	rgb_values[3];

	rgb_values[0] = ft_atoi(rgb[0]);
	rgb_values[1] = ft_atoi(rgb[1]);
	rgb_values[2] = ft_atoi(rgb[2]);
	if (rgb_values[0] < 0 || rgb_values[0] > 255
		|| rgb_values[1] < 0 || rgb_values[1] > 255
		|| rgb_values[2] < 0 || rgb_values[2] > 255)
		return (1);
	color->r = (float)rgb_values[0] / 255.0f;
	color->g = (float)rgb_values[1] / 255.0f;
	color->b = (float)rgb_values[2] / 255.0f;
	return (0);
}

int	parse_vector3(char *str, t_vect *vect)
{
	int		i;
	int		ret;
	char	**nbrs;

	i = -1;
	ret = 0;
	nbrs = ft_split(str, ',');
	while (nbrs && nbrs[++i])
		if (!is_valid_float_literal(nbrs[i]))
			ret = 1;
	if (string_array_length(nbrs) != 3)
		ret = 1;
	else
	{
		vect->x = parse_float_literal(nbrs[0]);
		vect->y = parse_float_literal(nbrs[1]);
		vect->z = parse_float_literal(nbrs[2]);
	}
	free_string_array(nbrs);
	return (ret);
}

int	parse_dual_color(char *str, t_color *color, t_color *color2)
{
	int		i;
	int		ret;
	char	**colors;

	i = -1;
	ret = 0;
	colors = ft_split(str, ';');
	if (string_array_length(colors) < 1)
		ret = 1;
	while (colors && colors[++i])
	{
		if (i == 0)
			ret = parse_rgb_color(colors[0], color);
		if (i == 1)
			ret = parse_rgb_color(colors[1], color2);
	}
	free_string_array(colors);
	return (ret);
}

int	parse_rgb_color(char *str, t_color *color)
{
	int		i;
	int		ret;
	char	**rgb;

	i = -1;
	ret = 0;
	rgb = ft_split(str, ',');
	while (rgb && rgb[++i])
		if (!is_valid_unsigned_number(rgb[i]))
			ret = 1;
	if (string_array_length(rgb) != 3)
		ret = 1;
	else if (parse_rgb_triplet(rgb, color))
		ret = 1;
	free_string_array(rgb);
	return (ret);
}

int	parse_float_value(char *str, float *num)
{
	if (!is_valid_float_literal(str))
		return (1);
	*num = parse_float_literal(str);
	return (0);
}
