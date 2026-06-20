/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 05:57:20 by kakubo-l          #+#    #+#             */
/*   Updated: 2026/06/20 05:57:21 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void Contact::setInfo(std::string first, std::string last, std::string nick, std::string number, std::string secret)
{
	_firstName = first;
	_lastName = last;
	_nickName = nick;
	_phoneNumber = number;
	_darkestSecret = secret;

}

std::string	Contact::truncate(std::string str )
{
	if (str.length() > 10)
	{
		return str.substr(0,9) + ".";
	}
	return str;
}

void Contact::display(int i)
{
	std::cout << std::setw(10) << i << "|"
			<< std::setw(10) << truncate(_firstName) << "|"
			<< std::setw(10) << truncate(_lastName) << "|"
			<< std::setw(10) << truncate(_nickName) << std::endl;
}

void Contact::fullDisplay()
{
	std::cout << "Primeiro nome: " << _firstName << std::endl;
	std::cout << "Sobrenome: " << _lastName << std::endl;
	std::cout << "Apelido: " << _nickName << std::endl;
	std::cout << "Telefone: " << _phoneNumber << std::endl;
	std::cout << "Segredo obscuro: " << _darkestSecret << std::endl;
}
