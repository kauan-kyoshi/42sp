/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 05:57:31 by kakubo-l          #+#    #+#             */
/*   Updated: 2026/07/07 17:07:10 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main()
{
	PhoneBook phoneNumbers;
	std::string cmd, confirm;

	while (true)
	{
		std::cout << "\nDigite um comando (ADD, SEARCH, EXIT): ";
		if (!std::getline(std::cin,cmd))
		{
			break;
		}
		if (cmd == "ADD")
		{
			phoneNumbers.add();
		}
		else if( cmd == "SEARCH")
		{
			phoneNumbers.search();
		}
		else if (cmd == "EXIT")
		{
			break;
		}
		else
		{
			std::cout << "Comando ignorado. User apenas ADD, SEARCH ou EXIT" << std::endl;
		}
	}
	return (0);

}