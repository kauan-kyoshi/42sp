/*
Assignment name  : ft_range
Expected files   : ft_range.c
Allowed functions: malloc
--------------------------------------------------------------------------------
Escreva a seguinte função:

int *ft_range(int start, int end);

Ela deve alocar (com malloc()) um array de inteiros, preenchê-lo com valores
consecutivos que começam em start e terminam em end (incluindo start e end!),
e então retornar um ponteiro para o primeiro valor do array.

Exemplos:

- With (1, 3) you will return an array containing 1, 2 and 3.
- With (-1, 2) you will return an array containing -1, 0, 1 and 2.
- With (0, 0) you will return an array containing 0.
- With (0, -3) you will return an array containing 0, -1, -2 and -3.
*/

#include <stdio.h>
#include <stdlib.h>

int *ft_range(int start, int end)
{
	int i;
	int j;
	int len;
	int *array;
	i =0;
	
	if (start < end)
	{
		len = (end - start) + 1;
		array = (int *)malloc(len * sizeof(int));

		j=start;
		while (j <= end)
		{
			array[i] = j;
			j++;
			i++;
		}
	}
	else if ( start > end)
	{	
		len = (start - end) +1;
		array = (int *)malloc(len * sizeof(int));
		j = start;

		while (i<len)
		{
			array[i] = j;
			j--;
			i++;
		}
		
	}
	else
	{
		len = 1;
		array = (int *)malloc(len * sizeof(int));
		array[0] = start;
	}

	return (array);
}

void print_array(int *arr, int len)
{
    if (arr == NULL)
    {
        printf("Array retornado é NULL.\n");
        return;
    }
    int i = 0;
    while (i < len)
    {
        printf("%d", arr[i]);
        if (i < len - 1)
        {
            printf(", ");
        }
        i++;
    }
    printf("\n");
}


int main(void)
{
    int *result;
    int len;

    // Exemplo 1: (1, 3)
    printf("Testando com (1, 3):\n");
    len = 3 - 1 + 1;
    result = ft_range(1, 3);
    print_array(result, len);
    free(result);

    printf("\n");

    // Exemplo 2: (-1, 2)
    printf("Testando com (-1, 2):\n");
    len = 2 - (-1) + 1;
    result = ft_range(-1, 2);
    print_array(result, len);
    free(result);

    printf("\n");

    // Exemplo 3: (0, 0)
    printf("Testando com (0, 0):\n");
    len = 0 - 0 + 1;
    result = ft_range(0, 0);
    print_array(result, len);
    free(result);

    printf("\n");

    // Exemplo 4: (0, -3)
    printf("Testando com (0, -3):\n");
    len = 0 - (-3) + 1;
    result = ft_range(0, -3);
    print_array(result, len);
    free(result);

    return 0;
}