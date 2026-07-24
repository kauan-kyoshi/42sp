#include "DiamondTrap.hpp"

int main()
{
	ClapTrap clap("Clappy");
	ScavTrap scav("Serena");
	FragTrap frag("Fragolina");
	DiamondTrap diamond("Mica");
	DiamondTrap copy(diamond);

	clap.attack("target zero");
	scav.attack("the intruder");
	scav.guardGate();
	frag.attack("the enemy");
	frag.highFivesGuys();
	diamond.attack("the boss");
	diamond.whoAmI();
	copy.whoAmI();
	copy.highFivesGuys();
	copy.guardGate();

	return (0);
}