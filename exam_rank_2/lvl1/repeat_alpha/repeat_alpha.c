/*
Assignment name  : repeat_alpha
Expected files   : repeat_alpha.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa chamado repeat_alpha que receba uma string e a exiba,
repetindo cada caractere alfabético tantas vezes quanto o seu índice alfabético,
seguido por uma nova linha.

'a' se torna 'a', 'b' se torna 'bb', 'e' se torna 'eeeee', etc.

A caixa (maiúscula/minúscula) permanece inalterada.

Se o número de argumentos não for 1, apenas exiba uma nova linha.

Examples:

$>./repeat_alpha "abc"
abbccc
$>./repeat_alpha "Alex." | cat -e
Alllllllllllleeeeexxxxxxxxxxxxxxxxxxxxxxxx.$
$>./repeat_alpha 'abacadaba 42!' | cat -e
abbacccaddddabba 42!$
$>./repeat_alpha | cat -e
$
$>
$>./repeat_alpha "" | cat -e
$
$>
*/
#include <unistd.h>

void ft_putchar(char c)
{
	write(1,&c,1);
}


int main (int argc, char **argv)
{
	int i;
	int j;
	i = 0;

	if (argc == 2)
	{
		while (argv[1][i] != '\0')
		{
			if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
			{
				j = 0;
				while(j < argv[1][i] - 96)
				{
					ft_putchar(argv[1][i]);
					j++;
				}
			}
			else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
			{
				j = 0;
				while (j < argv[1][i] - 64)
				{
					ft_putchar(argv[1][i]);
					j++;
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