/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 18:09:47 by cassunca          #+#    #+#             */
/*   Updated: 2026/06/05 01:10:18 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <memory>

Zombie*	newZombie( std::string name )
{
	Zombie* zombie = new Zombie(name);
	return (zombie);
}