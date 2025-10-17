/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:38:35 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/17 18:36:39 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>

t_dlist *dlist_new(void)
{
    t_dlist *new_list = (t_dlist *)malloc(sizeof(t_dlist));

    if (new_list == NULL)
        return (NULL);

    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;
    return (new_list);
}

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