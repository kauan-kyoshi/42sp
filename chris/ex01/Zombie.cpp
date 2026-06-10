/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 18:57:02 by cassunca          #+#    #+#             */
/*   Updated: 2026/06/10 16:31:35 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void    Zombie::setName( std::string name)
{
    this->name = name;
    std::cout << this->name << ": was created" << std::endl;
}

Zombie::Zombie( void ) {}

Zombie::~Zombie()
{
    std::cout << name << ": was destroyed" << std::endl;
}

void    Zombie::announce( void )
{
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
