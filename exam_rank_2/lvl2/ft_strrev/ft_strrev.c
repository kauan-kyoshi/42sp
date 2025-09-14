/*
Assignment name  : ft_strrev
Expected files   : ft_strrev.c
Allowed functions:
--------------------------------------------------------------------------------

Escreva uma função que inverta uma string (modificando a original).

Ela deve retornar o seu parâmetro.

Sua função deve ser declarada da seguinte forma:

char    *ft_strrev(char *str);
*/


char    *ft_strrev(char *str)
{
	int i;
	int j;
	char temp;
	i=0;
	j=0;

	while (str[i] != '\0')
	{
		i++;
	}
	while (j < i -1)
	{
		temp = str[j];
		str[j] = str[i - 1];
		str[i - 1] = temp;
		i--;
		j++;
	}
	return (str);
}
