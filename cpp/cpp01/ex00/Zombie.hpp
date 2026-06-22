#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include <string>
#include <iostream>
#include <memory>


class Zombie
{
	private:
			std::string name;

	public:
			Zombie(std::string name);
			void announce( void );
			~Zombie();
};

Zombie*	newZombie( std::string name );
void	randomChump( std::string name );

#endif
