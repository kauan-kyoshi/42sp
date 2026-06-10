#include "PhoneBook.hpp"


PhoneBook::PhoneBook()
{
	_count = 0;
}

void PhoneBook::add()
{
	std::string FirstName, LastName, NickName, PhoneNumber, Secret;
	int 		id;

	std::cout << "Primeiro Nome: ";
	std::getline(std::cin, FirstName);
	std::cout << "Sobrenome: ";
	std::getline(std::cin, LastName);
	std::cout << "Apelido: ";
	std::getline(std::cin, NickName);
	std::cout << "Número: ";
	std::getline(std::cin, PhoneNumber);
	std::cout << "Segredo mais obscuro: ";
	std::getline(std::cin, Secret);



	if (FirstName.empty() || LastName.empty() || NickName.empty() || PhoneNumber.empty() || Secret.empty())
	{
		std::cout << "Preencha todos os campos, por favor. \n";
		//testar sem retorno dps.
		return;
	}

	id = _count % 8;
	_contact[id] = FirstName, 


}