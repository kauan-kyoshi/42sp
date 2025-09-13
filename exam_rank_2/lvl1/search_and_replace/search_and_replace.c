/*
Assignment name  : search_and_replace
Expected files   : search_and_replace.c
Allowed functions: write, exit
--------------------------------------------------------------------------------

Crie um programa chamado search_and_replace que receba 3 argumentos. 
O primeiro argumento é uma string na qual você deve substituir um
caractere (o 2º argumento) por outro (o 3º argumento).

Se o número de argumentos não for 3, exiba apenas uma nova linha.

Se o segundo argumento não estiver contido no primeiro (a string), 
o programa deve simplesmente reescrever a string original seguida
 por uma nova linha.

Examples:
$>./search_and_replace "Papache est un sabre" "a" "o"
Popoche est un sobre
$>./search_and_replace "zaz" "art" "zul" | cat -e
$
$>./search_and_replace "zaz" "r" "u" | cat -e
zaz$
$>./search_and_replace "jacob" "a" "b" "c" "e" | cat -e
$
$>./search_and_replace "ZoZ eT Dovid oiME le METol." "o" "a" | cat -e
ZaZ eT David aiME le METal.$
$>./search_and_replace "wNcOre Un ExEmPle Pas Facilw a Ecrirw " "w" "e" | cat -e
eNcOre Un ExEmPle Pas Facile a Ecrire $
*/
#include <unistd.h>

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


int main (int argc, char **argv)
{
	int i;
	i = 0;

	if (argc == 4 && ft_strlen(argv[2]) == 1 && ft_strlen(argv[3]) == 1 )
	{
		while (argv[1][i] != '\0')
		{
			if (argv[1][i] == argv[2][0])
			{
				argv[1][i] = argv[3][0];
			}
			i++;
		}
		i=0;
		while (argv[1][i] != '\0')
		{
			ft_putchar(argv[1][i]);
			i++;
		}
	}
	ft_putchar('\n');	
}