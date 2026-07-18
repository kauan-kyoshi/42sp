#include "Zombie.hpp"

int main ()
{
	Zombie* horde = zombieHorde(15, "teste");
	delete[] horde;
	return 0;
}