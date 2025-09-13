/*
Assignment name  : rotone
Expected files   : rotone.c
Allowed functions: write
--------------------------------------------------------------------------------

Crie um programa que receba uma string e a exiba, substituindo cada uma de 
suas letras pela próxima na ordem alfabética. 'z' se torna 'a' e 'Z' se torna 'A'.
A caixa da letra permanece inalterada.

A saída será seguida por uma nova linha. Se o número de argumentos não for 1,
o programa exibirá uma nova linha.

Example:

$>./rotone "abc"
bcd
$>./rotone "Les stagiaires du staff ne sentent pas toujours tres bon." | cat -e
Mft tubhjbjsft ev tubgg of tfoufou qbt upvkpvst usft cpo.$
$>./rotone "AkjhZ zLKIJz , 23y " | cat -e
BlkiA aMLJKa , 23z $
$>./rotone | cat -e
$
$>
$>./rotone "" | cat -e
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
	i = 0;

	if (argc == 2)
	{
		while (argv[1][i] != '\0')
		{
			if((argv[1][i] >= 'a' && argv[1][i] <= 'y') || (argv[1][i] >= 'A' && argv[1][i] <= 'Y'))
			{
				ft_putchar(argv[1][i]+1);
			}
			else if (argv[1][i] == 'z')
			{
				ft_putchar('a');
			}
			else if (argv[1][i] == 'Z')
			{
				ft_putchar('A');
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