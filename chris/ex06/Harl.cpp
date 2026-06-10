/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 05:11:42 by cassunca          #+#    #+#             */
/*   Updated: 2026/06/05 05:25:02 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void	Harl::complain( std::string level )
{
	typedef void (Harl::*Harlfunc)();

	std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	Harlfunc funcs[4] = {
			&Harl::debug,
			&Harl::info,
			&Harl::warning,
			&Harl::error
	};

	for (int i = 0; i < 4; i++)
	{
		if (level == levels[i])
		{
			(this->*funcs[i])();
			return ;
		}
	}
}

void	Harl::debug( void )
{
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "Adição é a operação que junta dois grupos em um, agrupando ou somando suas quantidades." << std::endl;
}

void	Harl::info( void )
{
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "Multiplicação é adição repetida, ou seja, 4*4 tem o mesmo resultado que 4+4+4+4." << std::endl;
}

void	Harl::warning( void )
{
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "Subtração é o oposto da adição, tirando uma quantidade de outra." << std::endl;
}

void	Harl::error( void )
{
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "Divisão é o oposto da multiplicação, onde se checa quantos grupos de x elementos é possivel se fazer de uma  quantidade." << std::endl;
}