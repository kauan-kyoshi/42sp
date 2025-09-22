/*
Assignment name  : hidenp
Expected files   : hidenp.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa chamado hidenp que recebe duas strings e exibe 1, seguido 
por uma nova linha, se a primeira s tring estiver escondida na segunda. Caso 
contrário, exibe 0 seguido por uma nova linha.

Considere s1 e s2 como strings. Dizemos que s1 está escondida em s2 se for 
possível encontrar cada caractere de s1 em s2, na mesma ordem em que aparecem 
em s1. Além disso, a string vazia está escondida em qualquer string.

Se o número de parâmetros não for 2, o programa exibe uma nova linha.

Exemplos:

$>./hidenp "fgex.;" "tyf34gdgf;'ektufjhgdgex.;.;rtjynur6" | cat -e
1$
$>./hidenp "abc" "2altrb53c.sse" | cat -e
1$
$>./hidenp "abc" "btarc" | cat -e
0$
$>./hidenp | cat -e
$
$>

*/
#include <unistd.h>

int main (int argc, char **argv)
{
	if (argc == 3)
	{
		int i;
		int j;
		char *s1;
		char *s2;
		i=0;
		j=0;
		s1 = argv[1];
		s2 = argv[2];

		while (s1[i] != '\0' && s2[j] != '\0')
		{
			if (s1[i] == s2[j])
			{
				i++;
			}
			j++;
		}
		if (s1[i] == '\0')
		{
			write (1,"1",1);
		}
		else
		{
			write (1,"0",1);
		}
	}
	write(1,"\n",1);

}