/*
Assignment name  : do_op
Expected files   : *.c, *.h
Allowed functions: atoi, printf, write
--------------------------------------------------------------------------------

Escreva um programa que aceita três strings:

A primeira e a terceira string são representações de números inteiros com sinal,
de base 10, que cabem em um int.

A segunda string é um operador aritmético, escolhido entre: + - * / %.

O programa deve exibir o resultado da operação aritmética solicitada,
seguido por uma nova linha. Se o número de parâmetros não for 3,
o programa deve exibir apenas uma nova linha.

Você pode assumir que as strings não contêm erros ou caracteres extras. 
Números negativos, tanto na entrada quanto na saída, terão um e apenas 
um traço (-) à frente. O resultado da operação cabe em um int.

Examples:

$> ./do_op "123" "*" 456 | cat -e
56088$
$> ./do_op "9828" "/" 234 | cat -e
42$
$> ./do_op "1" "+" "-43" | cat -e
-42$
$> ./do_op | cat -e
$
*/

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
	int n1;
	int n2;
	int res;

	if (argc == 4)
	{
		n1 = atoi(argv[1]);
		n2 = atoi(argv[3]);
		if (argv[2][0] == '+')
		{
			res = n1 + n2;
		}
		else if (argv[2][0] == '-')
		{
			res =n1 - n2;
		}
		else if (argv[2][0] == '*')
		{
			res = n1 * n2;
		}
		else if (argv[2][0] == '/')
		{
			res = n1 / n2;
		}
		else if (argv[2][0] == '%')
		{
			res = n1 % n2;
		}
		printf("%d",res);
	}
	printf("\n");
}