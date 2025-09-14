/*
Assignment name  : inter
Expected files   : inter.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que recebe duas strings e exibe, sem duplicação, os caracteres que aparecem em ambas as strings, na ordem em que aparecem na primeira.

A exibição será seguida por um \n.

Se o número de argumentos não for 2, o programa exibe \n.

Examples:

$>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
padinto$
$>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6ewg4$
$>./inter "rien" "cette phrase ne cache rien" | cat -e
rien$
$>./inter | cat -e
$
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
	
	i=0;
	char asc[256] = {};

	if (argc == 3)
	{
		while (argv[1][i]!= '\0')
		{	
			j = 0;
			while (argv[2][j] != '\0')
			{
				if (argv[1][i] == argv[2][j])
				{
					if (asc[(int)argv[1][i]] == 0)
					{
						ft_putchar(argv[1][i]);
						asc[(int)argv[1][i]] = 1;
						break;
					}				
				}
				j++;
			}
			i++;
		}
	}
	ft_putchar('\n');
}