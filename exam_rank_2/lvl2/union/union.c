/*
Assignment name  : union
Expected files   : union.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que recebe duas strings e exibe, sem duplicações, 
os caracteres que aparecem em qualquer uma das strings.

A exibição será na ordem em que os caracteres aparecem na linha de comando e 
será seguida por um \n.

Se o número de argumentos não for 2, o programa exibe \n.

Example:

$>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
zpadintoqefwjy$
$>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6vewg4thras$
$>./union "rien" "cette phrase ne cache rien" | cat -e
rienct phas$
$>./union | cat -e
$
$>
$>./union "rien" | cat -e
$
$>
*/

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
int main (int argc, char **argv)
{
	int i;
	int j;
	i = 0;
	j = 0;
	char asc[256] = {};

	if (argc ==3)
	{
		while (argv[1][i] != '\0')
		{
			if(asc[argv[1][i]] == 0)
			{
				asc[argv[1][i]] = 1;
				ft_putchar(argv[1][i]);
			}	
			i++;
		}
		while (argv[2][j] != '\0')
		{
			if (asc[argv[2][j]] == 0)
			{
				asc[argv[2][j]] = 1;
				ft_putchar(argv[2][j]);
			}
			j++;
		}
	}
	ft_putchar('\n');
}