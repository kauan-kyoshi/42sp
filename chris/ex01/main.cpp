/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 18:53:55 by cassunca          #+#    #+#             */
/*   Updated: 2026/06/04 17:12:26 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main( void )
{
	int	N = 10;
	Zombie*	zombies = zombieHorde( N, "zombie" );
	delete[] zombies;
	return (0);
}