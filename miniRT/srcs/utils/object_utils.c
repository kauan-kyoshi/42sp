/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:33:03 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:32:15 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	*get_object_position(t_obj *obj)
{
	if (!obj)
		return (NULL);
	if (obj->id == id_plane)
		return (&obj->object.plane.coords);
	if (obj->id == id_sphere)
		return (&obj->object.sphere.coords);
	if (obj->id == id_cone)
		return (&obj->object.cone.coords);
	if (obj->id == id_cylinder)
		return (&obj->object.cylinder.coords);
	return (NULL);
}

void	append_object(t_obj *obj, t_obj **objs)
{
	t_obj	*tmp;

	if (!(*objs))
		*objs = obj;
	else
	{
		tmp = *objs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = obj;
	}
}

t_obj	*alloc_object(t_rt *rt, t_obj_id id)
{
	t_obj	*obj;

	obj = ft_calloc(sizeof(t_obj), 1);
	obj->id = id;
	obj->speckv = SPECULAR_KV;
	obj->specn = SPECULAR_N;
	obj->mirror = MIRROR;
	obj->refract = REFRACT;
	obj->pattern_len = PATTERN_LEN;
	obj->pattern_num = PATTERN_NUM;
	obj->has_bump = FALSE;
	obj->texture.img = NULL;
	obj->has_texture = FALSE;
	obj->bump.img = NULL;
	append_object(obj, &rt->objs);
	rt->num_objs++;
	return (obj);
}

void	destroy_objects(t_rt *rt, t_obj **objs)
{
	t_obj	*tmp;
	t_obj	*obj;

	obj = *objs;
	(void)rt;
	while (obj)
	{
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
	*objs = 0;
}
