/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:28:03 by kyoshi            #+#    #+#             */
/*   Updated: 2025/10/11 23:02:08 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int *convert_arr(int argc, char **argv)
{
	int *arr;
	int i;
	int j; 
	int num;
	
	arr = malloc_pile(argc);
	i = 1;
	j = 0;
	while(i <= argc -1)
	{
		num = ft_atoi(argv[i]);
		arr[j] = num;
		j++;
		i++;
	}
	return(arr);
}