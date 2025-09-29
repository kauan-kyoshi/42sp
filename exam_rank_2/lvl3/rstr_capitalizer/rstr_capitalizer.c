/*
Assignment name  : rstr_capitalizer
Expected files   : rstr_capitalizer.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que receba uma ou mais strings e, para cada argumento, 
coloque a última letra de cada palavra em maiúscula e o restante em minúsculas,
em seguida exiba o resultado seguido de uma nova linha.

Uma palavra é uma seção de string delimitada por espaços/tabulações ou pelo 
início/fim da string. Se uma palavra tiver uma única letra, ela deve ser 
maiúscula.

Uma letra é um caractere no conjunto [a-zA-Z].

Se não houver parâmetros, exiba uma nova linha.

Exemplos:

$> ./rstr_capitalizer | cat -e
$
$> ./rstr_capitalizer "a FiRSt LiTTlE TESt" | cat -e
A firsT littlE tesT$
$> ./rstr_capitalizer "SecONd teST A LITtle BiT   Moar comPLEX" "   But... This iS not THAT COMPLEX" "     Okay, this is the last 1239809147801 but not    the least    t" | cat -e
seconD tesT A littlE biT   moaR compleX$
   but... thiS iS noT thaT compleX$
     okay, thiS iS thE lasT 1239809147801 buT noT    thE leasT    T$
$>
*/

#include <unistd.h>

void ft_putchar(char c)
{
	write(1,&c,1);
}

int is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
	{
		return(1);
	}
	else
	{
		return(0);
	}
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
	int args;
	int len;
	if (argc >= 2)
	{
		args = 1;
		while (args < argc)
		{
			i=0;
			len = ft_strlen(argv[args]);
			while (argv[args][i] != '\0')
			{
				if (argv[args][i] >= 'A' && argv[args][i] <= 'Z')
				{
					argv[args][i] += 32;
				}
				i++;
			}
			i=0;
			while (argv[args][i] != '\0')
			{
				if ((argv[args][i] >= 'a' && argv[args][i] <= 'z') && (is_space(argv[args][i+1]) || i == len -1))
				{
					argv[args][i] -= 32;
				}
				i++;
			}
			i=0;
			while (argv[args][i] != '\0')
			{
				ft_putchar(argv[args][i]);
				i++;
			}

			ft_putchar('\n');
			args++;

		}
		

	}
	else
	{
		ft_putchar('\n');
	}
	

}