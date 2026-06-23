#include "Zombie.hpp"

Zombie::Zombie(void) : name("")
{

}

void    Zombie::setName( std::string name)
{
    this->name = name;
    std::cout << this->name << ": was born" << std::endl;
}

Zombie::~Zombie()
{
	std::cout << name << ": died" << std::endl;
}

void Zombie::announce( void )
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}