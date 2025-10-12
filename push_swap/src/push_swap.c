/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:38:35 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/11 23:01:35 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>

void push_swap(int argc, char **argv)
{
	int *arr;
	arr = convert_arr(argc, argv);
	
	int i =0;
	while (i < argc -1)
	{
		printf("%d\n",arr[i]);
		i++;
	}
	free(arr);
}