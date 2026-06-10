/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 18:57:33 by cassunca          #+#    #+#             */
/*   Updated: 2026/06/02 19:47:45 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
    if (N <= 0)
        return (NULL);

    Zombie*	zombie_horde = new Zombie[N];
        
    for (int i = 0; i < N; i++)
    {
        std::stringstream	ss;

		ss << i;
        
        zombie_horde[i].setName(name + ss.str());
		zombie_horde[i].announce();
    }
	return (zombie_horde);
}