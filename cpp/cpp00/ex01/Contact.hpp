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

};






#endif