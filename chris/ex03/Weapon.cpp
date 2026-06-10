/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 18:35:41 by cassunca          #+#    #+#             */
/*   Updated: 2026/06/04 20:42:07 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon( const std::string& type ) : type(type) {}

const	std::string& Weapon::getType() const
{
	return (type);
}

void	Weapon::setType( const std::string& type)
{
	this->type = type;
}