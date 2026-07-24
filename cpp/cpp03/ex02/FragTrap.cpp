#include "FragTrap.hpp"

#include <iostream>

FragTrap::FragTrap()
	: ClapTrap("FragTrap")
{
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string &name)
	: ClapTrap(name)
{
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	std::cout << "FragTrap " << _name << " constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &other)
	: ClapTrap(other)
{
	std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &other)
{
	if (this != &other)
		ClapTrap::operator=(other);
	std::cout << "FragTrap copy assignment operator called" << std::endl;
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << _name << " destructor called" << std::endl;
}

void	FragTrap::attack(const std::string &target)
{
	if (_hitPoints == 0 || _energyPoints == 0)
	{
		std::cout << "FragTrap " << _name << " can't attack" << std::endl;
		return ;
	}
	--_energyPoints;
	std::cout << "FragTrap " << _name << " attacks " << target
		<< ", causing " << _attackDamage << " points of damage!" << std::endl;
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << _name << " requests a positive high five!" << std::endl;
}