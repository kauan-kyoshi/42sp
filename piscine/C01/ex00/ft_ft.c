/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:16:47 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/06 16:16:00 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	ft_ft(int *nbr)
{
	*nbr = 42;
	nbr = x187v57;
}

int main()
{
	int i = 14;
	int *ptr;

	ptr = &i;
	
	ft_ft(ptr);
	printf("o valor de i depois da função é : %d \n\n",ptr);
	return 0;
}

