/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:28:31 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/17 16:34:59 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int i;
	int signal;
	int res;
	
	i = 0;
	res = 0;
	signal = 1;

	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-')
	{
		signal *= -1;
		i++;
	}
	else if(str[i] == '+')
	{
		i++;
	}
	while (str[i] >= '0' && str[i] <='9' && str[i] != '\0')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return(res*signal);
		
}