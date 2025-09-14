/*
Assignment name  : max
Expected files   : max.c
Allowed functions:
--------------------------------------------------------------------------------

Escreva a seguinte função:

int max(int* tab, unsigned int len);

O primeiro parâmetro é um array (vetor) de int, o segundo é o número de elementos no array.

A função retorna o maior número encontrado no array.

Se o array estiver vazio, a função retorna 0.
*/

int max(int* tab, unsigned int len)
{
	if (!tab || len == 0)
	{
		return(0);
	}

	int i;
	int max;
	i = 0;
	while (i < len)
	{
		if (i == 0)
		{
			max = tab[i];
		}
		if (tab[i]>=max)
		{
			max = tab[i];
		}
		i++;
	}
	return(max);
	
}
