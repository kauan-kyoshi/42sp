#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	if (N <=0)
	{
		return (NULL);
	}

	Zombie* zombie_horde = new Zombie[N];


	int i = 0;

	while (i < N)
	{
		std::stringstream to_st;

		to_st << name << ' ' << (i+1);

		zombie_horde[i].setName(to_st.str());
		zombie_horde[i].announce();
		i++;
	}
	return (zombie_horde);
}