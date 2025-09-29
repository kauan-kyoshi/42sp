/*
Assignment name  : sort_int_tab
Expected files   : sort_int_tab.c
Allowed functions:
--------------------------------------------------------------------------------

Escreva a seguinte função:

void sort_int_tab(int *tab, unsigned int size);

Ela deve ordenar (in-place) o array de inteiros 'tab', que contém exatamente 
'size' membros, em ordem crescente.
Valores duplicados devem ser preservados.
A entrada será sempre coerente.

*/
void	sort_int_tab(int *tab, unsigned int size)
{
	int tmp;
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < size - 1)
	{
		j = i;
		while (j < size)
		{
			if (tab[i] > tab[j])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
