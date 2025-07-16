/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:01:07 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/17 19:28:12 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int check_doubles1(char *str, char c, int pos)
{
	int i;
	
	i = 0;
	while (i < pos)
	{
		if(str[i] == c)
		{
			return(0);
		}
		i++;
	}
	return(1);
}

int check_doubles2(char *str, char c, int pos)
{
	int i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void ft_union(char *str, char *str1)
{
	int i;
	i = 0;
	
	while (condition)
	{
		/* code */
	}
	
}