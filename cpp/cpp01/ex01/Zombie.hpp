#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include <string>
#include <iostream>
#include <memory>
#include <sstream>

class Zombie
{
	private:
			std::string name;

	public:
			Zombie(void);
			void announce( void );
			void    setName( std::string name);
			~Zombie();
};

Zombie* zombieHorde( int N, std::string name );

#endif
