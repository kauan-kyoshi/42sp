/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:35:26 by cassunca          #+#    #+#             */
/*   Updated: 2026/06/05 01:09:23 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>

void	replaceLine( std::string& line, const std::string& s1, const std::string& s2);

int	main(int ac, char **av)
{
	std::string line, file, s1, s2;
	
	if (ac != 4)
	{
		std::cout << "Usage: " << av[0] << " <file> <s1> <s2>" << std::endl; 
		return (1);
	}
	
	file = av[1];
	s1 = av[2];
	s2 = av[3];

	std::ifstream ss(av[1]);

	if (!ss.is_open())
	{
		std::cerr << "Error: couldn't open input file" << std::endl;
		return (1);
	}
	
	std::ofstream replace((file + ".replace").c_str());

	if (!replace.is_open())
	{
		std::cerr << "Error: couldn't opem output file" << std::endl;
		ss.close();
		return (1);
	}

	while (std::getline(ss, line))
	{
		replaceLine(line, s1, s2);
		replace << line << std::endl;
	}

	ss.close();
	replace.close();
	
	return (0);
}

void	replaceLine( std::string& line, const std::string& s1, const std::string& s2)
{
	size_t	pos = 0;
	
	if (s1.empty())
		return ;
		
	while ((pos = line.find(s1, pos)) != std::string::npos)
	{
		line.erase(pos, s1.size());
		line.insert(pos, s2);
		pos += s2.size();
	}
}