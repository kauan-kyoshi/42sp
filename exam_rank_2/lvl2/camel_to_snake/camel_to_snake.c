/*
Assignment name  : camel_to_snake
Expected files   : camel_to_snake.c
Allowed functions: malloc, realloc, write
--------------------------------------------------------------------------------

Escreva um programa que aceita uma única string no formato lowerCamelCase
e a converte para uma string no formato snake_case.

Uma string lowerCamelCase é uma string onde cada palavra começa com uma letra 
maiúscula, exceto a primeira.

Uma string snake_case é uma string onde cada palavra está em letras minúsculas,
separadas por um sublinhado "_".

Examples:
$>./camel_to_snake "hereIsACamelCaseWord"
here_is_a_camel_case_word
$>./camel_to_snake "helloWorld" | cat -e
hello_world$
$>./camel_to_snake | cat -e
$

*/

#include <unistd.h>
#include <stdlib.h>

void ft_putchar(char c)
{
	write(1,&c,1);
}
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
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i;
    
    if (argc == 2)
    {
        i = 0;

        while (argv[1][i]!= '\0')
        {
            if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
            {
                argv[1][i] += 32;
                ft_putchar('_');
            }
            ft_putchar(argv[1][i]);
            i++;
        }
    }
    write(1, "\n", 1);
}