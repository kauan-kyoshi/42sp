/*
Assignment name  : snake_to_camel
Expected files   : snake_to_camel.c
Allowed functions: malloc, free, realloc, write
--------------------------------------------------------------------------------

Escreva um programa que recebe uma única string no formato snake_case e a
converte para uma string no formato lowerCamelCase.

Uma string snake_case é uma string onde cada palavra está em minúsculas,
separada por um underscore (sublinhado) _.

Uma string lowerCamelCase é uma string onde cada palavra começa com uma letra
maiúscula, exceto a primeira.

Examples:
$>./snake_to_camel "here_is_a_snake_case_word"
hereIsASnakeCaseWord
$>./snake_to_camel "hello_world" | cat -e
helloWorld$
$>./snake_to_camel | cat -e
$
*/

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
int main (int argc, char **argv)
{
	int i;
	i = 0;

	if (argc == 2)
	{
		while (argv[1][i] != '\0')
		{
			if (argv[1][i] == '_')
			{
				i++;
				if (argv[1][i]>= 'a' && argv[1][i] <= 'z')
				{
					argv[1][i] -= 32;
					ft_putchar(argv[1][i]);
				}
			}
			else
			{
				ft_putchar(argv[1][i]);
			}
			i++;
		}
		
	}
	ft_putchar('\n');
}