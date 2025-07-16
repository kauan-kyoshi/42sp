/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:40:33 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/10 21:25:59 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

Assignment name  : first_word
Expected files   : first_word.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays its first word, followed by a
newline.

A word is a section of string delimited by spaces/tabs or by the start/end of
the string.

If the number of parameters is not 1, or if there are no words, simply display
a newline.

Examples:

$> ./first_word "FOR PONY" | cat -e
FOR$
$> ./first_word "this        ...       is sparta, then again, maybe    not" | cat -e
this$
$> ./first_word "   " | cat -e
$
$> ./first_word "a" "b" | cat -e
$
$> ./first_word "  lorem,ipsum  " | cat -e
lorem,ipsum$
$>
*/

#include <unistd.h>

int main(int argc, char **argv)
{
	int i;
	i=0;

	if (argc == 2)
	{
		while(argv[1][i] == '\t' || argv[1][i] == ' ')
			{
				i++;
			}
		while(argv[1][i] != '\0' && argv[1][i] != ' ' && argv[1][i] != '\t')
			{
				write(1,&argv[1][i],1);
				i++;
			}
			
			
	}
	write(1,"\n",1);
	return(0);
		
}
