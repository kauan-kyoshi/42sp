/*
Assignment name  : add_prime_sum
Expected files   : add_prime_sum.c
Allowed functions: write, exit
--------------------------------------------------------------------------------

Escreva um programa que receba um número inteiro positivo como argumento e exiba
a soma de todos os números primos inferiores ou iguais a ele, seguido por uma
nova linha.

Se o número de argumentos não for 1, ou se o argumento não for um número positivo,
exiba apenas 0 seguido por uma nova linha.

Sim, os exemplos estão corretos.

Examples:

$>./add_prime_sum 5
10
$>./add_prime_sum 7 | cat -e
17$
$>./add_prime_sum | cat -e
0$
$>
*/
#include <unistd.h>
int ft_atoi(char *n)
{
	int i;
	int sign;
	int res;
	res = 0;
	i=0;
	sign = 1;
	while (n[i] <=32)
	{
		i++;
	}
	if (n[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (n[i] == '+')
    {
        i++;
    }
	while (n[i] >= '0' && n[i] <= '9')
	{
		res *= 10;
		res += n[i] - '0';
		i++;
	}
	return (res*sign);
	
}
void ft_putchar(char c)
{
	write(1,&c,1);
}
 
void ft_putnbr(int n)
{
	if (n >= 10)
	{
		ft_putnbr(n/10);
	}
	ft_putchar((n % 10) + '0');
}
int	ft_is_prime(int nb)
{
	int	n;

	n = 2;
	if (nb < 2)
	{
		return (0);
	}
	while (n < nb)
	{
		if (nb % n == 0)
		{
			return (0);
		}
		n++;
	}
	return (1);
}

int main (int argc, char **argv)
{


	if(argc == 2)
	{
		int num;
		int sum;
		int prime;
		sum = 0;
		num = ft_atoi(argv[1]);
		
		if (num <= 0)
		{
			write(1,"0\n",2);
			return(0);
		}
		
		while (num >= 0)
		{
			prime = ft_is_prime(num);
			if (prime == 1)
			{
				sum+=num;
			}
			num--;
		}
		ft_putnbr(sum);
		ft_putchar('\n');
	}
	else
	{
		write(1,"0\n",2);
	}
}