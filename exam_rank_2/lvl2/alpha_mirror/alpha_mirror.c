/*
Assignment name  : alpha_mirror
Expected files   : alpha_mirror.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa chamado alpha_mirror que aceita uma string e exibe essa
string depois de substituir cada caractere alfabético pelo caractere alfabético
oposto, seguido por uma nova linha.

'a' torna-se 'z', 'Z' torna-se 'A'
'd' torna-se 'w', 'M' torna-se 'N'

e assim por diante.

A caixa não é alterada (maiúsculas e minúsculas).

Se o número de argumentos não for 1, exiba apenas uma nova linha.

Examples:

$>./alpha_mirror "abc"
zyx
$>./alpha_mirror "My horse is Amazing." | cat -e
Nb slihv rh Znzarmt.$
$>./alpha_mirror | cat -e
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
		while(argv[1][i] != '\0')
		{
			if (argv[1][i]>= 'A' && argv[1][i] <= 'Z' )
			{
				argv[1][i] = 'Z' - argv[1][i] + 'A';
			}
			else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
			{
				argv[1][i] = 'z' - argv[1][i] + 'a';
			}
			ft_putchar(argv[1][i]);
			i++;
		}
	}
	ft_putchar('\n');
}

/*
	fazer o Z - o caractere + o A
*/