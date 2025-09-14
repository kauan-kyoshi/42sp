/*
Assignment name  : is_power_of_2
Expected files   : is_power_of_2.c
Allowed functions: None
--------------------------------------------------------------------------------
Escreva uma função que determina se um dado número é uma potência de 2.

Esta função retorna 1 se o número fornecido for uma potência de 2, caso contrário, retorna 0.

Sua função deve ser declarada da seguinte forma:

int	    is_power_of_2(unsigned int n);
*/

int	    is_power_of_2(unsigned int n)
{
	int i;
	i=1;

	while( i <= n)
	{
		if (i == n)
		{
			return(1);
		}
		i *= 2;
	}
	return(0);
}
