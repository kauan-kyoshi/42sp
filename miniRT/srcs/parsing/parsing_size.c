/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:20:00 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:25 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_size_value(char *str, size_t *num)
{
	if (!is_valid_unsigned_number(str))
		return (1);
	*num = (size_t)ft_atoi(str);
	return (0);
}
