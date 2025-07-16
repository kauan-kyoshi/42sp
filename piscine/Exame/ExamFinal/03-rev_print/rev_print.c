/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:38:10 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/17 13:55:14 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : rev_print
Expected files   : rev_print.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a function that takes a string and displays the string in reverse
order followed by the newline.
Its prototype is constructed like this : 
  char *ft_rev_print (char *str)
It must return its argument

Examples:

$> ./rev_print "zaz" | cat -e
zaz$
$> ./rev_print "dub0 a POIL" | cat -e
LIOP a 0bud$
$> ./rev_print | cat -e
$
*/
#include <unistd.h>

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return(i);
	
}


char *ft_rev_print (char *str)
{
	int i;
	int j;
	char temp;
	i = 0;
	j = ft_strlen(str) - 1;

	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	i = 0;
	while (str[i] != '\0')
	{
		write(1,&str[i],1);
		i++;
	}
	write(1,"\n",1);
	return(str);
	
}

int main (int argc, char **argv)
{
	if (argc == 2)
	{
		ft_rev_print(argv[1]);
	}	
}