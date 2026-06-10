/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 18:27:39 by cassunca          #+#    #+#             */
/*   Updated: 2026/06/02 18:35:26 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie*	newZombie( std::string name );
void	randomChump( std::string name );

int	main( void )
{
	randomChump("(random)Tufid");
	Zombie* ryuji = newZombie("(new)Ryuji");
	ryuji->announce();
	randomChump("(random)Sephir");
	Zombie* illidan = newZombie("(new)Illidan");
	illidan->announce();
	delete	ryuji;
	delete	illidan;
	return (0);
}