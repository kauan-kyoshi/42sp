/*
Assignment name  : fizzbuzz
Expected files   : fizzbuzz.c
Allowed functions: write
--------------------------------------------------------------------------------

Escreva um programa que imprima os números de 1 a 100, cada um em uma nova linha.

    Se o número for um múltiplo de 3, imprima 'fizz' em vez do número.

    Se o número for um múltiplo de 5, imprima 'buzz' em vez do número.

    Se o número for um múltiplo de 3 e de 5, imprima 'fizzbuzz' em vez do número.

Example:

$>./fizzbuzz
1
2
fizz
4
buzz
fizz
7
8
fizz
buzz
11
fizz
13
14
fizzbuzz
[...]
97
98
fizz
buzz
$>
*/
#include <unistd.h>

void ft_putchar(char c)
{
	write(1,&c,1);
}

void ft_putnbr(int n)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10);
	}
	ft_putchar((n % 10) +'0');

	
}


int main (void)
{
	int i;
	i = 1;

	while (i <= 100)
	{
		if (i % 3 == 0 && i % 5 == 0)
			write(1, "fizzbuzz", 8);
		else if (i % 3 == 0)
			write(1,"fizz",4);
		else if(i % 5 == 0)
			write(1,"buzz",4);
		else
			ft_putnbr(i);
		write(1,"\n",1);

		i++;
	}
	

	return 0; 
}