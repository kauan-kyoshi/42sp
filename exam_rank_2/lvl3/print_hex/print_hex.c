/*
Assignment name  : print_hex
Expected files   : print_hex.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que receba um número positivo (ou zero) expresso em base 
10 e o exiba em base 16 (letras minúsculas), seguido por uma nova linha.

Se o número de parâmetros não for 1, o programa exibe uma nova linha.
Examples:

$> ./print_hex "10" | cat -e
a$
$> ./print_hex "255" | cat -e
ff$
$> ./print_hex "5156454" | cat -e
4eae66$
$> ./print_hex | cat -e
$

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
	int sign;
	sign = 1;
	i = 0;
	res = 0;

	while(str[i] <= 32 )
	{
		i++;
	}
	if(str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	while(str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return(res*sign);
}

void ft_puthex(int n)
{
	char *hex = "0123456789abcdef";
	int num;
	num = n;
	if(num >= 16)
	{
		ft_puthex(num/16);
	}

	ft_putchar(hex[num%16]);
}

int main (int argc, char **argv)
{
	int n;
	if(argc == 2)
	{	n = ft_atoi(argv[1]);
		ft_puthex(n);
	}
	ft_putchar('\n');

}
