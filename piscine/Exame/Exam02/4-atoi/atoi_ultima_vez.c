/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_ultima_vez.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:25:22 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/12 17:41:37 by kakubo-l         ###   ########.fr       */
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
	
	
	i =0;
	signal=1;
	res=0;
	while ((str[i]>= '\t' && str[i] <= '\r') ||str[i] == ' ')
	{
		i++;
	}
	if (str[i]== '-')
	{
		signal *= -1;
		i++; 
	}
	else if (str[i] == '+')
	{
		i++;
	}
	while (str[i] != '\0' && str[i] >='0' && str[i]<='9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return(res*signal);
	
}
