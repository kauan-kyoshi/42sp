/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:19:22 by kyoshi            #+#    #+#             */
/*   Updated: 2025/07/12 21:34:54 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(char *str)
{
    int i;
    int signal;
    int res;

    i = 0;
    signal = 1;
    res = 0;
    while (str[i] == ' ' || (str[i] >= '\t'&& str[i] <= '\r'))
        i++;
    if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
    while (str[i] >= '0' && str[i] <='9')
    {
        res = (res * 10) + (str[i] - '0');
        i++;
    }
    return (res * signal);
}