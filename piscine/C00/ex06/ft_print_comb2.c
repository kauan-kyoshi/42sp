/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:09:35 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/05/31 19:27:18 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_put2char(char d, char u)
{
	write(1, &d, 1);
	write(1, &u, 1);
}

void	ft_putnumber(int n, int lim)
{
	char	ch_d;
	char	ch_u;

	if (n <= 9)
	{
		ch_u = n + 48;
		ft_put2char('0', ch_u);
	}
	else if (n <= lim)
	{
		ch_u = (n % 10) + 48;
		ch_d = (n / 10) + 48;
		ft_put2char(ch_d, ch_u);
	}
}

void	ft_putcommon(void)
{
	write(1, ",", 1);
	write(1, " ", 1);
}

void	ft_concat(int one, int two)
{
	ft_putnumber(one, 98);
	write(1, " ", 1);
	ft_putnumber(two, 99);
	if (one != 98 || two != 99)
	{
		ft_putcommon();
	}
}

void	ft_print_comb2(void)
{
	int	first;
	int	second;

	first = 0;
	while (first <= 98)
	{
		second = first + 1;
		while (second <= 99)
		{
			ft_concat(first, second);
			second++;
		}
		first++;
	}
}
