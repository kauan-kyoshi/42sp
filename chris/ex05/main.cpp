/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 04:57:40 by cassunca          #+#    #+#             */
/*   Updated: 2026/06/05 05:03:11 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void	testLevel(Harl harl, const std::string& test)
{
	std::cout << std::endl;
	std::cout << "------ Testing" << " ------" << std::endl;
	harl.complain(test);
}

int	main( void )
{
	Harl	harl;
	testLevel(harl, "DEBUG");
	testLevel(harl, "INFO");
	testLevel(harl, "WARNING");
	testLevel(harl, "ERROR");

	return (0);
}