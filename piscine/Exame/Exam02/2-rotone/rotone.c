/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:09:05 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/12 10:50:23 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : rotone
Expected files   : rotone.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays it, replacing each of its
letters by the next one in alphabetical order.

'z' becomes 'a' and 'Z' becomes 'A'. Case remains unaffected.

The output will be followed by a \n.

If the number of arguments is not 1, the program displays \n.

Example:

$>./rotone "abc"
bcd
$>./rotone "Les stagiaires du staff ne sentent pas toujours tres bon." | cat -e
Mft tubhjbjsft ev tubgg of tfoufou qbt upvkpvst usft cpo.$
$>./rotone "AkjhZ zLKIJz , 23y " | cat -e
BlkiA aMLJKa , 23z $
$>./rotone | cat -e
$
$>
$>./rotone "" | cat -e
$
$>
*/

#include <unistd.h>

void ft_rotone(char c)
{
	char i;
	i = c+1;
	write(1, &i, 1);
}

int main (int argc, char **argv)
{
	int i;
	
	i = 0;
	if (argc == 2)
	{
		while (argv[1][i] != '\0')
		{
			if ((argv[1][i] >= 'a' && argv[1][i] <='y') || (argv[1][i] >= 'A' && argv[1][i] <= 'Y'))
			{
				ft_rotone(argv[1][i]);
			}
			else if(argv[1][i] == 'z')
			{
				write(1, "a", 1);
			}
			else if(argv[1][i] == 'Z')
			{
				write(1, "A", 1);
			}
			else{
				write(1,&argv[1][i],1);
			}
			
			i++;
		}
	}
	write(1, "\n", 1);	
}