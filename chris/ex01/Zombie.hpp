/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 18:45:04 by cassunca          #+#    #+#             */
/*   Updated: 2026/06/04 17:16:59 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <string>
# include <sstream>

class Zombie
{
	private:
		std::string name;

	public:
		Zombie( void );
		~Zombie( void );
		void	announce( void );
		void	setName( std::string name );
};

Zombie*	zombieHorde( int N, std::string name );

#endif