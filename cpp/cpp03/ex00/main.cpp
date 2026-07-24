#include "ClapTrap.hpp"

int main()
{
	ClapTrap a("Alpha");
	ClapTrap b(a);

	a.attack("target one");
	a.takeDamage(3);
	a.beRepaired(2);

	b.attack("target two");
	b.takeDamage(10);
	b.beRepaired(1);

	return (0);
}
