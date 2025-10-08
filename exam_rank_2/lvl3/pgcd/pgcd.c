/*
Assignment name  : pgcd
Expected files   : pgcd.c
Allowed functions: printf, atoi, malloc, free
--------------------------------------------------------------------------------

Escreva um programa que recebe duas strings que representam dois inteiros 
estritamente positivos que cabem em um int.

Exiba o maior divisor comum deles, seguido por uma nova linha (é sempre 
um inteiro estritamente positivo).

Se o número de parâmetros não for 2, exiba uma nova linha.

Exemplos:

$> ./pgcd 42 10 | cat -e
2$
$> ./pgcd 42 12 | cat -e
6$
$> ./pgcd 14 77 | cat -e
7$
$> ./pgcd 17 3 | cat -e
1$
$> ./pgcd | cat -e
$

*/

#include <stdio.h>
#include <stdlib.h>

int maior(int n1, int n2)
{
	if (n1 > n2)
	{
		return(n1);
	}
	else
	{
		return(n2);
	}
	
}

int main (int argc, char **argv)
{
	if (argc == 3)
	{
		int i, n1, n2, res;
		i = 1;
		n1 = atoi(argv[1]);
		n2 = atoi(argv[2]);

		
		while (i<=maior(n1,n2))
		{
			if(n1 % i ==0 && n2 % i == 0)
			{
				res = i;
			}
			i++;
		}
		
		printf("%d",res);


	}
	printf("\n");
}