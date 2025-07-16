/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:21:03 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/16 16:40:02 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>

int		*ft_range(int min, int max)
{
	int *ptr;
	int i;

	if (min >= max)
	{
		return (0);
	}
	ptr = malloc(max - min);
	if (ptr == NULL)
	{
		return (0);
	}
	i = 0;
	while (min < max)
	{
		ptr[i] = min;
		i++;
		min++;
	}
	return (ptr);
}