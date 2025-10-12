/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_pile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 19:06:23 by kyoshi            #+#    #+#             */
/*   Updated: 2025/10/11 19:11:48 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int *malloc_pile(int argc)
{
	int *arr;
	int len;
	len = argc -1;
	
	arr = malloc(len*sizeof(int));
	if(!arr)
	{
		return(0);
	}
	return(arr);
}