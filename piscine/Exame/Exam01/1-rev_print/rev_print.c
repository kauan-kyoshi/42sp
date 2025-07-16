/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:59:20 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/06/05 11:11:42 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

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

char *ft_rev_print (char *str)
{   
    int i;
    i = ft_strlen(str) - 1;
    
    while (i>=0)
    {
        write(1,&str[i],1);
        i--;
    }
    return(str);
}

int main()
{
    char test[] = "testando";
    ft_rev_print(test);
}