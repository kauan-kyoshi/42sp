#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{

	Weapon sword = Weapon("long sword");
	HumanA humanA1("Human A1", sword);
	humanA1.attack();
	sword.setType("short sword");
	humanA1.attack();

	std::cout << std::endl;

	Weapon bow = Weapon("recurve bow");
	HumanB HumanB1("Human B1");
	HumanB1.setWeapon(bow);
	HumanB1.attack();
	bow.setType("long bow");
	HumanB1.attack();

	std::cout << std::endl;

	Weapon pistol = Weapon("glock");
	HumanA humanA2("Human A2", pistol);
	// humanA2.attack();
	pistol.setType("p250");
	// humanA2.attack();

	Weapon ar = Weapon("ak-47");
	HumanB HumanB2("Human B2");
	// HumanB2.setWeapon(ar);
	HumanB2.attack();
	ar.setType("m4a1");
	HumanB2.attack();

	return 0;
}
