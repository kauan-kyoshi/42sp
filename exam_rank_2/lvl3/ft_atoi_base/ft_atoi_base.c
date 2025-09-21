/*
Assignment name  : ft_atoi_base
Expected files   : ft_atoi_base.c
Allowed functions: None
--------------------------------------------------------------------------------
Escreva uma função que converte o argumento de string str (base N <= 16) para um número inteiro (base 10) e o retorna.

Os caracteres reconhecidos na entrada são: 0123456789abcdef.
Esses caracteres, é claro, devem ser limitados de acordo com a base solicitada. Por exemplo, a base 4 reconhece "0123" e a base 16 reconhece "0123456789abcdef".

Letras maiúsculas também devem ser reconhecidas: "12fdb3" é o mesmo que "12FDB3".

Sinais de menos ('-') são interpretados apenas se forem o primeiro caractere da string.

Sua função deve ser declarada da seguinte forma:

int	ft_atoi_base(const char *str, int str_base);
*/
#include <stdio.h>

int convert(char c)
{
	if(c >= '0' && c <= '9')
	{
		return(c - '0');
	}
	else if (c >= 'a' && c <= 'f')
	{
		return (c - 'a' +10);
	}
	else if(c >= 'A' && c <= 'F')
	{
		return(c - 'A' + 10);
	}
	else
		return(-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int i, sign, res, digit;
	i=0,
	sign = 1;
	res = 0;

	if (str_base < 2 || str_base > 16)
        return (0);

	while ((str[i] == 32) || (str[i]>= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' )
	{
		sign *= -1;
		i++;
	}
	else if(str[i] == '+')
	{
		i++;
	}

	while ((str[i] >='0' && str[i] <='9') || (str[i] >= 'a' && str[i] <='f') || (str[i] >= 'A' && str[i] <= 'F'))
	{

		digit = convert(str[i]);

		if (digit == -1 || digit >= str_base)
		{
			break;
		}
		
		res = res * str_base + digit;
		i++;
	}
	
	return(res*sign);
}
int main()
{
    printf("Base 10: %d\n", ft_atoi_base("123", 10));        // Saída: 123
    printf("Base 16: %d\n", ft_atoi_base("1aF", 16));        // Saída: 431
    printf("Base 2: %d\n", ft_atoi_base("1010", 2));       // Saída: 10
    printf("Com sinal: %d\n", ft_atoi_base("-2f", 16));    // Saída: -47
    printf("Com espaços: %d\n", ft_atoi_base("  +1010", 2)); // Saída: 10
    printf("Base inválida: %d\n", ft_atoi_base("123", 17));   // Saída: 0
    printf("Caracteres inválidos: %d\n", ft_atoi_base("123abc", 10)); // Saída: 123
    return 0;
}