#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
	ClapTrap clap("Clappy");
	ScavTrap scav("Serena");
	FragTrap frag("Fragolina");
	FragTrap copy(frag);

	clap.attack("target zero");
	scav.attack("the intruder");
	scav.guardGate();
	frag.attack("the enemy");
	frag.highFivesGuys();
	copy.takeDamage(25);
	copy.beRepaired(15);
	copy.highFivesGuys();

	return (0);
}