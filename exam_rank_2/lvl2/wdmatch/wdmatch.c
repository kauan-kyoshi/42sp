/*
Assignment name  : wdmatch
Expected files   : wdmatch.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que recebe duas strings e verifica se é possível escrever a
primeira string com os caracteres da segunda, respeitando a ordem em que esses
caracteres aparecem na segunda string.

Se for possível, o programa exibe a primeira string, seguida por um \n.
Caso contrário, ele simplesmente exibe um \n.

Se o número de argumentos não for 2, o programa exibe um \n.

Examples:

$>./wdmatch "faya" "fgvvfdxcacpolhyghbreda" | cat -e
faya$
$>./wdmatch "faya" "fgvvfdxcacpolhyghbred" | cat -e
$
$>./wdmatch "quarante deux" "qfqfsudf arzgsayns tsregfdgs sjytdekuoixq " | cat -e
quarante deux$
$>./wdmatch "error" rrerrrfiiljdfxjyuifrrvcoojh | cat -e
$
$>./wdmatch | cat -e
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
	int j;
	i=0;
	j=0;

	if (argc == 3)
	{
		while (argv[2][j] != '\0')
		{
			if (argv[1][i] == argv[2][j])
			{
				i++;
			}
			
			j++;
		}
		if(argv[1][i] == '\0')
		{
			i=0;
			while (argv[1][i] != '\0')
			{
				ft_putchar(argv[1][i]);
				i++;
			}
			
		}
	}
	ft_putchar('\n');
}