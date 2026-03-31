/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:32:33 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:32:15 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	append_light(t_light *new_light, t_light **lights)
{
	t_light	*tmp;

	if (!(*lights))
		*lights = new_light;
	else
	{
		tmp = *lights;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_light;
	}
}

t_light	*alloc_light(t_rt *rt)
{
	t_light	*new_light;

	new_light = ft_calloc(sizeof(t_light), 1);
	if (!new_light)
		return (0);
	new_light->id = id_light;
	append_light(new_light, &rt->light);
	return (new_light);
}

void	destroy_lights(t_light **lights)
{
	t_light	*tmp;
	t_light	*light;

	light = *lights;
	while (light)
	{
		tmp = light;
		light = light->next;
		free(tmp);
	}
	*lights = 0;
}
