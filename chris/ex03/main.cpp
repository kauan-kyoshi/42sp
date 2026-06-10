/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 17:51:08 by cassunca          #+#    #+#             */
/*   Updated: 2026/06/10 16:43:34 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int	main( void )
{
	std::cout << "*** HUMAN A ATTACKS ***" << std::endl;
	{
		Weapon	tatical = Weapon("long bow");

		HumanA	elf("Illidan", tatical);
		elf.attack();
		tatical.setType("dagger");
		elf.attack();
	}
	std::cout << std::endl << "*** HUMAN B ATTACKS WITH WEAPON ***" << std::endl;
	{
		Weapon	sword = Weapon("short sword");

		HumanB	human("Tufid");
		human.setWeapon(sword);
		human.attack();
		sword.setType("long sword");
		human.attack();
	}
	std::cout << std::endl << "*** HUMAN B ATTACKS WITHOUT WEAPON ***" << std::endl;
	{
		Weapon	sword = Weapon("Tiranah");

		HumanB	human("Tufid");
		human.attack();
	}
	return (0);
}