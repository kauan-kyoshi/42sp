/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:00:33 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/09 14:56:30 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_rev_int_tab(int *tab, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	j = size - 1;
	while (i < j)
	{
		temp = tab[i];
		tab[i] = tab[j];
		tab[j] = temp;
		i++;
		j--;
	}
}

int main(){
	int i;
	i = 0;
	int test[8] = {1,2,3,4,5,6,7,8};
	ft_rev_int_tab(test,8);

	while (i <8)
	{
		printf("%d", test[i]);
		i++;
	}
	
	
	
}
