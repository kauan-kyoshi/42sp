#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"


class PhoneBook
{
	private:

			Contact _contact[8];
			int 	_count;

	public:
			PhoneBook();
			void add();
			void search();
};



#endif