#include "vbc.h"


char *s;


void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}


int ft_product()
{
	int a = ft_factor();
	int b;
	while (*s == '*')
	{
		s++;
		b = ft_factor();
		a = a*b;
	}
	return a;
}


int ft_sum()
{
	int a = ft_product();
	int b;
	while (*s == '+')
	{
		s++;
		b = ft_product();
		a = a+b;
	}
	return a;
}

int	ft_factor()
{
	int n = 0;
	if (isdigit(*s))
	{
		return (*s++ - '0');
	}

	while (*s =='(')
	{
		s++;
		n = ft_sum();
		s++;
	}
	return n;

}

int check_input(char *str)
{
	int par =0;
	int i=0;
	char last = 0;

	while (str[i])
	{
		if (str[i] )
		{
			/* code */
		}

	}

}