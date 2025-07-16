/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:27:01 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/10 20:38:31 by kakubo-l         ###   ########.fr       */
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

int ft_strlen(char *str){
	int i;
	
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return(i);	
}

char *ft_rev_print (char *str){
	int len;

	len = ft_strlen(str) - 1;
	while (len >= 0)
	{
		write(1,&str[len],1);
		len--;
	}
	return(str);
	
}


int main()
{
	char str[] = "testando";
	ft_rev_print(str);
}