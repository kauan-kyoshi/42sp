#include "ScavTrap.hpp"

int main()
{
	ClapTrap clap("Clappy");
	ScavTrap scav("Serena");
	ScavTrap copy(scav);

	clap.attack("target zero");
	scav.attack("the intruder");
	scav.guardGate();
	copy.attack("another intruder");
	copy.takeDamage(42);
	copy.beRepaired(10);

	return (0);
}