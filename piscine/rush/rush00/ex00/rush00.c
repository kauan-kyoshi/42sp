/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:27:15 by plucas-s          #+#    #+#             */
/*   Updated: 2025/06/01 15:44:07 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char ch);

void	rush(int x, int y)
{
	int	l;
	int	c;

	l = 1;
	while (l <= y && x > 0)
	{
		c = 1;
		while (c <= x)
		{
			if ((l == 1 && c == 1) || (l == y && c == 1)
				|| (l == 1 && c == x) || (l == y && c == x))
				ft_putchar('o');
			else if ((c == 1 && (l != 1 || l != y))
				|| (c == x && (l != 1 || l != y)))
				ft_putchar('|');
			else if ((l == 1 && (c != 1 && c != x))
				|| (l == y && (c != 1 && c != x)))
				ft_putchar('-');
			else
				ft_putchar(' ');
			c++;
		}
		ft_putchar('\n');
	l++;
	}
}
