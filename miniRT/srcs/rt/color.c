/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:29:21 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:42:11 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	make_color(float red, float green, float blue)
{
	t_color	color;

	color.r = red;
	color.g = green;
	color.b = blue;
	return (color);
}

t_color	*scale_color_inplace(t_color *color, float factor)
{
	color->r *= color->r * factor;
	color->g *= color->g * factor;
	color->b *= color->b * factor;
	return (color);
}

t_color	scale_color(t_color color, float factor)
{
	color.r *= color.r * factor;
	color.g *= color.g * factor;
	color.b *= color.b * factor;
	return (color);
}

t_color	unpack_rgb_color(int packed_rgb)
{
	t_color	color;

	color.r = (float)((packed_rgb >> 16) & 0xff) / 255;
	color.g = (float)((packed_rgb >> 8) & 0xff) / 255;
	color.b = (float)(packed_rgb & 0xff) / 255;
	return (color);
}

int	pack_rgb_color(t_color color)
{
	int	packed_rgb;

	packed_rgb = (int)(color.r * 255) << 16;
	packed_rgb += (int)(color.g * 255) << 8;
	packed_rgb += (int)(color.b * 255);
	return (packed_rgb);
}
