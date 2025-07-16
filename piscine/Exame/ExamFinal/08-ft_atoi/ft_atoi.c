/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:39:54 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/17 14:55:33 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : ft_atoi
Expected files   : ft_atoi.c
Allowed functions: None
--------------------------------------------------------------------------------

Write a function that converts the string argument str to an integer (type int)
and returns it.

It works much like the standard atoi(const char *str) function, see the man.

Your function must be declared as follows:

int	ft_atoi(const char *str);

*/

int	ft_atoi(const char *str)
{
	int i;
	int signal;
	int res;
	
	res = 0;
	signal = 1;
	i =0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-')
	{
		signal *= -1;
		i++;	
	}
	else if (str[i] == '+')
	{
		i++;
	}
	while (str[i] != 0 && str[i]>= '0' && str[i] <= '9')
	{
		res = (res *10)+(str[i] - '0');
		i++;
	}
	return(res * signal);
}