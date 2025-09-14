/*
Assignment name  : last_word
Expected files   : last_word.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que recebe uma string e exibe sua última palavra, seguida por um \n.

Uma palavra é um trecho da string delimitado por espaços/tabs ou pelo início/fim da string.

Se o número de parâmetros não for 1, ou se não houver palavras, exiba uma nova linha.

Example:

$> ./last_word "FOR PONY" | cat -e
PONY$
$> ./last_word "this        ...       is sparta, then again, maybe    not" | cat -e
not$
$> ./last_word "   " | cat -e
$
$> ./last_word "a" "b" | cat -e
$
$> ./last_word "  lorem,ipsum  " | cat -e
lorem,ipsum$
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
	i = 0;

	if (argc == 2)
	{
		//vai até o final
		while (argv[1][i] != '\0')
		{
			i++;
		}
		//ultima letra
		i--;
		//retira os espaços | i >= 0 para verificar se é o inicio da string.
		while (i >= 0 && argv[1][i] <= ' ')
		{
			i--;
		}
		// vai até o inicio da ultima palavra
		while ( i >= 0 && argv[1][i] > ' ')
		{
			i--;
		}
		//encontra a primeira letra da ultima palavra
		i++;
		//imprime a ultima palavra
		while ((argv[1][i] != ' ' && argv[1][i] != '\t') && argv[1][i] != '\0' )
		{
			ft_putchar(argv[1][i]);
			i++;
		}
	}
	ft_putchar('\n');
}