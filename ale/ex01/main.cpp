/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:56:50 by alessandro        #+#    #+#             */
/*   Updated: 2026/06/02 16:06:11 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int	main()
{
	PhoneBook myBook;
	std::string command;

	std::cout << "Bem-vindo a Sua Incível Agenda Telefonica dos anos 80!" << std::endl;

	while (true)
	{
		std::cout << "\n Digite um comando (ADD, SEARCH, EXIT): ";
		if (!std::getline(std::cin, command))
		{
			break;
		}
		if (command == "ADD")
		{
			myBook.add();
		}
		else if (command == "SEARCH")
		{
			myBook.search();
		}
		else if (command == "EXIT")
		{
			std::cout << "Encerrando o programa... Contatos perdidos para sempre!" << std::endl;
			break;
		}
		else
		{
			std::cout << "Comando ignorado. User apenas ADD, SEARCH ou EXIT" << std::endl;
		}
	}
	return (0);
}
