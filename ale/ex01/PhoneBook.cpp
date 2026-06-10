/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:50:10 by alessandro        #+#    #+#             */
/*   Updated: 2026/06/10 14:49:22 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	_count = 0;
}

void PhoneBook::add()
{
	std::string firstName, lastName, nickName, phoneNumber, secret;

	std::cout << "Primeiro nome: ";
	std::getline(std::cin, firstName);
	std::cout << "Sobrenome: ";
	std::getline(std::cin, lastName);
	std::cout << "Apelido: ";
	std::getline(std::cin, nickName);
	std::cout << "Telefone: ";
	std::getline(std::cin, phoneNumber);
	std::cout << "Segredo obscuro: ";
	std::getline(std::cin, secret);

	if (firstName.empty() || lastName.empty() || nickName.empty() ||
		phoneNumber.empty() || secret.empty())
	{
		std::cout << "Erro: Nenum campo pode estar vazio!" << std::endl;
		return;
	}
	int index = _count % 8;
	_contacts[index].setInfo(firstName, lastName, nickName, phoneNumber, secret);
	_count++;
}

void PhoneBook::search()
{
	std::cout << "Índice    |Nome      |Sobrenome |Apelido   " << std::endl;

	int max = (_count > 8) ? 8 : _count;
	for (int i = 0; i < max; i++)
	{
		_contacts[i].displayShort(i);
	}

	std::cout << "Digite o índice do contato para ver o detalhe: ";
	int index;
	std::cin >> index;

	if (std::cin.fail() || index < 0 || index >= max)
	{
		std::cout << "Índice inválido!" << std::endl;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}
	else
	{
		_contacts[index].displayFull();
	}
	std::cin.ignore(10000, '\n');
}
