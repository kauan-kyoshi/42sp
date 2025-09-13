/*
Assignment name  : ft_strlen
Expected files   : ft_strlen.c
Allowed functions:
--------------------------------------------------------------------------------

Escreva uma função que retorne o comprimento de uma string. 
Sua função deve ser declarada da seguinte forma: 

`int ft_strlen(char *str);`
*/

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
