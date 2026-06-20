/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 05:57:27 by kakubo-l          #+#    #+#             */
/*   Updated: 2026/06/20 05:57:28 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <string>
#include <iomanip>


class Contact
{
	private:
			std::string _firstName;
			std::string _lastName;
			std::string _nickName;
			std::string _phoneNumber;
			std::string _darkestSecret;
	public:
			void setInfo(std::string first, std::string last, std::string nick, std::string number, std::string secret);
			void display(int i);
			void fullDisplay();
			std::string truncate(std::string str);

};






#endif