/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 05:57:52 by kakubo-l          #+#    #+#             */
/*   Updated: 2026/06/20 05:57:53 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "megaphone.hpp"

void ft_putstr_cap(char *str)
{
	int i;
	i =0;
	while(str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
		{
			str[i] = str[i]-32;
		}

		std::cout.put(str[i]);
		i++;
	}
}


int main(int argc, char **argv)
{
	if (argc > 1)
	{
		int i ;
		i=1;

		while(i < argc)
		{
			ft_putstr_cap(argv[i]);
			i++;
		}
		std::cout << ("\n");
	}
	else
	{
		std::cout << ("* LOUD AND UNBEARABLE FEEDBACK NOISE *");
		std::cout << ("\n");

	}

}