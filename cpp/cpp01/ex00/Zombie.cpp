#include "Zombie.hpp"


Zombie::Zombie(std::string name) : name(name)
{

}
Zombie::~Zombie()
{
	std::cout << name << ": died" << std::endl;
}

void Zombie::announce( void )
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}