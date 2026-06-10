/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:42:09 by alessandro        #+#    #+#             */
/*   Updated: 2026/06/02 15:55:10 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

static	std::string truncate(std::string str)
{
	if (str.length() > 10)
	{
		return str.substr(0, 9) + ".";
	}
	return (str);
}

void	Contact::setInfo(std::string first, std::string last, std::string nick,
						std::string phone, std::string secret)
{
	_firstName = first;
	_lastName = last;
	_nickName = nick;
	_phoneNumber = phone;
	_darkestSecret = secret;
}

void	Contact::displayShort(int index)
{
	std::cout << std::setw(10) << index << "|"
			<< std::setw(10) << truncate(_firstName) << "|"
			<< std::setw(10) << truncate(_lastName) << "|"
			<< std::setw(10) << truncate(_nickName) << std::endl;
}

void	Contact::displayFull()
{
	std::cout << "Primeiro nome: " << _firstName << std::endl;
	std::cout << "Sobrenome: " << _lastName << std::endl;
	std::cout << "Apelido: " << _nickName << std::endl;
	std::cout << "Telefone: " << _phoneNumber << std::endl;
	std::cout << "Segredo obscuro: " << _darkestSecret << std::endl;
}
