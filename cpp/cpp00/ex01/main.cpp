#include "PhoneBook.hpp"

int main()
{
	PhoneBook phoneNumbers;
	std::string cmd, confirm;

	while (true)
	{
		std::cout << "\n Digite um comando (ADD, SEARCH, EXIT): ";
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
			std::cout << "Todos os contatos serão perdidos para sempre, deseja continuar? S/N" << std::endl;
			getline(std::cin,confirm);
			while (confirm != "N" && confirm != "S")
			{
				std::cout << "S/N" << std::endl;
				getline(std::cin, confirm);
			}

			if (confirm == "S")
			{
				std::cout << "Até a próxima!!" << std::endl;
				break;
			}
			else if (confirm == "N")
			{
				continue;
			}
		}
		else
		{
			std::cout << "Comando ignorado. User apenas ADD, SEARCH ou EXIT" << std::endl;
		}
	}
	return (0);

}