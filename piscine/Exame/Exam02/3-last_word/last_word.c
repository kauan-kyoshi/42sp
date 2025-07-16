/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:12:32 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/12 12:39:13 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name  : last_word
Expected files   : last_word.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays its last word followed by a \n.

A word is a section of string delimited by spaces/tabs or by the start/end of
the string.

If the number of parameters is not 1, or there are no words, display a newline.

Example:

$> ./last_word "FOR PONY" | cat -e
PONY$
$> ./last_word "this        ...       is sparta, then again, maybe    not" | cat -e
not$
$> ./last_word "   " | cat -e
$
$> ./last_word "a" "b" | cat -e
$
$> ./last_word "a" "b" | cat -e
lorem,ipsum$
$>
*/

#include <unistd.h>

int ft_strlen(char *str)
{
	int i;

	i=0;
	while (str[i] != '\0')
	{
		i++;
	}
	return(i);
}

int main (int argc, char **argv)
{
	
	if (argc == 2)
	{
		int len;
		
		len = ft_strlen(argv[1]) - 1;
		
		while (len >= 0)
		{
			if (argv[1][len] == ' ' || argv[1][len] == '\t')
			{
				break;
			}
			len--;
		}
		while (argv[1][len] != '\0')
		{
			write(1,&argv[1][len],1);
			len++;
		}
		
	}
	write(1,"\n",1);
	
	
}