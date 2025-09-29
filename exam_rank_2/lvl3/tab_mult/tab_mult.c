/*
Assignment name  : tab_mult
Expected files   : tab_mult.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que exiba a tabuada de um número.

O parâmetro será sempre um número estritamente positivo que cabe em um int, e 
esse número multiplicado por 9 também caberá em um int.

Se não houver parâmetros, o programa exibe uma nova linha.

Exemplos:

$>./tab_mult 9
1 x 9 = 9
2 x 9 = 18
3 x 9 = 27
4 x 9 = 36
5 x 9 = 45
6 x 9 = 54
7 x 9 = 63
8 x 9 = 72
9 x 9 = 81
$>./tab_mult 19
1 x 19 = 19
2 x 19 = 38
3 x 19 = 57
4 x 19 = 76
5 x 19 = 95
6 x 19 = 114
7 x 19 = 133
8 x 19 = 152
9 x 19 = 171
$>
$>./tab_mult | cat -e
$
$>

*/

#include <unistd.h>

void ft_putchar(char c)
{
	write(1,&c,1);
}

int ft_atoi(char *str)
{
	int i;
	int res;

	i=0;
	res=0;

	while (str[i] >= '0' && str[i] <= '9')
	{
		res *=10;
		res += str[i] - '0';
		i++;
	}
	return(res);
}
void ft_putnbr(int n)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10);
	}
	ft_putchar((n % 10) +'0');

}

int main (int argc, char **argv)
{
	int mult;
	int n;

	if(argc == 2)
	{	n = ft_atoi(argv[1]);
		mult = 1;
		while (mult < 10)
		{
			putnbr(mult);
			ft_putchar(' ');
			ft_putchar('x');
			ft_putchar(' ');
			putnbr(n);
			ft_putchar(' ');
			ft_putchar('=');
			ft_putchar(' ');
			putnbr(n*mult);
			ft_putchar('\n');
			mult++;
		}
	}
	ft_putchar('\n');
}