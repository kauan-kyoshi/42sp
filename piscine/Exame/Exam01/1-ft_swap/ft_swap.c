/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:47:17 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/05 10:56:51 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_swap(int *a, int *b)
{
    
    int c;
    
    c = *a;
    *a = *b;
    *b = c;
}

int main(int argc, char const *argv[])
{
    int i;
    int j;
    
    i=10;
    j=5;
    
    printf("valor de  i : %d \n valor de j : %d \n \n",i,j);
    
    ft_swap(&i,&j);
    
    printf("valor de  i : %d \n valor de j : %d",i,j);
    return 0;
}
