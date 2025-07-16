/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_13.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:43:22 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/11 11:27:06 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
Assignment name  : rot_13
Expected files   : rot_13.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays it, replacing each of its
letters by the letter 13 spaces ahead in alphabetical order.

'z' becomes 'm' and 'Z' becomes 'M'. Case remains unaffected.

The output will be followed by a newline.

If the number of arguments is not 1, the program displays a newline.

Example:

$>./rot_13 "abc"
nop
$>./rot_13 "My horse is Amazing." | cat -e
Zl ubefr vf Nznmvat.$
$>./rot_13 "AkjhZ zLKIJz , 23y " | cat -e
NxwuM mYXVWm , 23l $
$>./rot_13 | cat -e
$
$>
$>./rot_13 "" | cat -e
$
$>

*/

#include <unistd.h>

void rot_plus_13(char c){
	char i;
	i= c+13;
	write(1, &i, 1);
}

void rot_minus_13(char c)
{
	char i;
	i = c - 13;
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
			if ((argv[1][i] >= 'a' && argv[1][i] <= 'm') || (argv[1][i] >= 'A' && argv[1][i] <= 'M'))
			{
				rot_plus_13(argv[1][i]);
			}
			else if ((argv[1][i] >= 'n' && argv[1][i] <= 'z') || (argv[1][i] >= 'N' && argv[1][i] <= 'Z'))
			{
				rot_minus_13(argv[1][i]);
			}
			else{
				write(1,&argv[1][i],1);
			}
			i++;
		}
		
	}
	write(1, "\n", 1);
	
}