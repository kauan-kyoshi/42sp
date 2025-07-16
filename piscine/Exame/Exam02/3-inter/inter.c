/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:00:20 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/12 12:10:02 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : inter
Expected files   : inter.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes two strings and displays, without doubles, the
characters that appear in both strings, in the order they appear in the first
one.

The display will be followed by a \n.

If the number of arguments is not 2, the program displays \n.

Examples:

$>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
padinto$
$>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6ewg4$
$>./inter "rien" "cette phrase ne cache rien" | cat -e
rien$
$>./inter | cat -e
$
*/

#include <unistd.h>

int doubles(char *str, char c, int pos)
{
	int i;

	i = 0;

	while (i < pos)
	{
		if (str[i]==c)
		{
			return (0);
		}
		i++;
	}
	return (1);
	
}

int main (int argc, char **argv){
	
	if (argc == 3)
	{
		int i;
		int j;
		i=0;
		while (argv[1][i] != '\0')
		{
			j=0;
			while (argv[2][j] != '\0')
			{
				if (argv[1][i] == argv[2][j])
				{
					if (doubles(argv[1],argv[1][i],i) == 1)
					{
						write(1,&argv[1][i],1);
						break;
					}
				}
				j++;
			}
			i++;
		}
	}
	write(1,"\n",1);
	return(0);
}