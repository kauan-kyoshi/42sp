/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 05:25:14 by cassunca          #+#    #+#             */
/*   Updated: 2026/06/10 17:06:59 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void	testLevel(Harl harl, const std::string test)
{
	std::cout << std::endl;
	std::cout << "----- Testing" << " -----" << std::endl;
	harl.complain(test);
}

int	main(int ac, char **av)
{
	Harl	harl;

	if (ac != 2)
	{
		std::cout << "Invalid number of arguments." << std::endl;
		return (1);
	}

	std::string	level = av[1];
	std::string levels[4] = {
			"DEBUG",
			"INFO",
			"WARNING",
			"ERROR"
	};

	int	start = -1;

	for (int i = 0; i < 4; i++)
	{
		if (level == levels[i])
		{
			start = i;
			break;
		}
	}

	if (start < 0)
	{
		std::cout << "[ Provavelmente reclamando sobre problemas insignificantes ]" << std::endl;
		return (1);
	}

	for (int i = start; i < 4; i++)
		testLevel(harl, levels[i]);

	return (0);
}