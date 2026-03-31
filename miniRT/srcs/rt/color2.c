/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:29:34 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	apply_light_contribution(t_color base_color,
		t_color light_color, float intensity)
{
	t_color	lit_color;

	if (intensity > 1)
		intensity = 1;
	if (intensity < 0)
		intensity = 0;
	lit_color.r = base_color.r * light_color.r * intensity;
	lit_color.g = base_color.g * light_color.g * intensity;
	lit_color.b = base_color.b * light_color.b * intensity;
	if (lit_color.r > 1)
		lit_color.r = 1;
	if (lit_color.g > 1)
		lit_color.g = 1;
	if (lit_color.b > 1)
		lit_color.b = 1;
	if (lit_color.r < 0)
		lit_color.r = 0;
	if (lit_color.g < 0)
		lit_color.g = 0;
	if (lit_color.b < 0)
		lit_color.b = 0;
	return (lit_color);
}

t_color	blend_colors(t_color color_a, float weight_a,
		t_color color_b, float weight_b)
{
	t_color	mixed_color;

	mixed_color.r = color_a.r * weight_a + color_b.r * weight_b;
	mixed_color.g = color_a.g * weight_a + color_b.g * weight_b;
	mixed_color.b = color_a.b * weight_a + color_b.b * weight_b;
	return (mixed_color);
}

int	average_color_samples(t_color	sample_colors[9])
{
	t_color	accumulated_color;
	int		sample_index;

	sample_index = 0;
	accumulated_color = make_color(0, 0, 0);
	while (sample_index < 9)
	{
		accumulated_color.r += sample_colors[sample_index].r;
		accumulated_color.g += sample_colors[sample_index].g;
		accumulated_color.b += sample_colors[sample_index].b;
		sample_index++;
	}
	accumulated_color.r /= 9;
	accumulated_color.g /= 9;
	accumulated_color.b /= 9;
	return (pack_rgb_color(accumulated_color));
}

t_color	resolve_object_color(t_obj *obj, t_hit *hit)
{
	float	texture_uv[2];
	t_color	color;

	color = obj->color;
	if (obj->id == id_sphere && obj->has_texture)
	{
		map_sphere_uv(obj, hit->phit, texture_uv);
		color = sample_texture_color(&obj->texture,
				texture_uv[0], texture_uv[1]);
	}
	else if (obj->pattern_num > 0)
		color = resolve_pattern_color(obj, hit->phit);
	return (color);
}
