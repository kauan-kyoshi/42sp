/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:31:33 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 16:32:16 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	toggle_flag(int *flag)
{
	if (*flag)
		*flag = 0;
	else
		*flag = 1;
}

int	on_key_down(int key, t_rt *rt)
{
	if (key == ESC_KEY)
		handle_window_close(rt);
	rt->event.key[key] = 1;
	if (key == I_KEY)
	{
		toggle_flag(&rt->display_info);
		render_frame(rt);
	}
	if (key == A_KEY)
	{
		toggle_flag(&rt->img.antialiasing_on);
		render_frame(rt);
	}
	return (0);
}

int	on_key_up(int key, t_rt *rt)
{
	rt->event.key[key] = 0;
	return (0);
}
