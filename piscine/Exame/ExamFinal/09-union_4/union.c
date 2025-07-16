/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:43:41 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/17 19:00:00 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : union
Expected files   : union.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes two strings and displays, without doubles, the
characters that appear in either one of the strings.

The display will be in the order characters appear in the command line, and
will be followed by a \n.

If the number of arguments is not 2, the program displays \n.

Example:

$>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
zpadintoqefwjy$
$>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6vewg4thras$
$>./union "rien" "cette phrase ne cache rien" | cat -e
rienct phas$
$>./union | cat -e
$
$>
$>./union "rien" | cat -e
$
$>
*/

#include <unistd.h>

int check_doubles1(char *str, char c, int pos)
{
	int i;

	i = 0;
	while (i < pos)
	{
		if (str[i] == c)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int check_doubles2(char *str, char c)
{
	int i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			return (0);
		}
		i++;
	}
	return(1);
}

void ft_union(char *str, char *str1)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (check_doubles1(str,str[i],i) == 1)
		{
			write(1,&str[i],1);
		}
		i++;
	}
	i = 0;
	while (str1[i] != '\0')
	{
		if (check_doubles2(str,str1[i]) == 1)
		{
			if (check_doubles1(str1,str1[i],i) == 1 )
			{
				write(1,&str1[i],1);
			}
			
		}
		i++;
	}
}

int main (int argc, char **argv)
{
	
	if(argc ==3)
	{
		ft_union(argv[1],argv[2]);
	}
	write(1,"\n",1);
}