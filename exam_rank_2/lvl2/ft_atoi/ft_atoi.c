/*
Assignment name  : ft_atoi
Expected files   : ft_atoi.c
Allowed functions: None
--------------------------------------------------------------------------------

Escreva uma função que converte o argumento de string str para um inteiro 
(do tipo int) e o retorna.

Ela funciona de forma muito similar à função padrão atoi(const char *str),
consulte o manual (man).

Sua função deve ser declarada da seguinte forma:

int ft_atoi(const char *str);

*/

int ft_atoi(const char *str)
{
	int i;
	int sing;
	int res;

	i = 0;
	sing = 1;
	res = 0;

	while ((str[i] >=9 && str[i] <= 13) || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-')
	{
		sing = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <='9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return(res*sing);
	
	
	
}