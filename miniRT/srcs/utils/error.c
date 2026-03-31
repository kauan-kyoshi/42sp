/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:32:25 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:00:18 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	report_parsing_error(t_rt *rt, char **arr, char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(msg, 2);
	if (rt->lnum)
	{
		ft_putstr_fd(" [line:", 2);
		ft_putnbr_fd(rt->lnum, 2);
		ft_putstr_fd(":param:", 2);
		ft_putnbr_fd(rt->pnum + 1, 2);
		ft_putstr_fd("]", 2);
	}
	ft_putendl_fd("", 2);
	free_string_array(arr);
	return (1);
}

int	report_error(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd("", 2);
	return (1);
}
