#include "ClapTrap.hpp"

#include <iostream>

ClapTrap::ClapTrap()
	: _name("ClapTrap"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
	: _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap " << _name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other)
	: _name(other._name), _hitPoints(other._hitPoints),
	  _energyPoints(other._energyPoints), _attackDamage(other._attackDamage)
{
	std::cout << "ClapTrap copy constructor called" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
	if (this != &other)
	{
		_name = other._name;
		_hitPoints = other._hitPoints;
		_energyPoints = other._energyPoints;
		_attackDamage = other._attackDamage;
	}
	std::cout << "ClapTrap copy assignment operator called" << std::endl;
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << _name << " destructor called" << std::endl;
}

void	ClapTrap::attack(const std::string &target)
{
	if (_hitPoints == 0 || _energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " can't attack" << std::endl;
		return ;
	}
	--_energyPoints;
	std::cout << "ClapTrap " << _name << " attacks " << target
		<< ", causing " << _attackDamage << " points of damage!" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " is already down" << std::endl;
		return ;
	}
	if (amount >= static_cast<unsigned int>(_hitPoints))
		_hitPoints = 0;
	else
		_hitPoints -= amount;
	std::cout << "ClapTrap " << _name << " takes " << amount << " points of damage!" << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoints == 0 || _energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " can't be repaired" << std::endl;
		return ;
	}
	--_energyPoints;
	_hitPoints += amount;
	std::cout << "ClapTrap " << _name << " be repaired for " << amount << " hit points!" << std::endl;
}