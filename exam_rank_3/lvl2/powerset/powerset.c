#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função recursiva que gera todos os subconjuntos com soma = target
// index: índice atual no array de números
// current: array que armazena o subconjunto atual
// current_size: tamanho do subconjunto atual
// current_sum: soma atual dos elementos do subconjunto
// target: soma alvo
// numbers: array de números do conjunto
// count: número de elementos no conjunto
void find_subsets(int index, int *current, int current_size, int current_sum,
	int target, int *numbers, int count)
{
	int i;

	// Se encontrou um subconjunto com soma = target
	if (current_sum == target)
	{
		// Imprime o subconjunto
		i = 0;
		while (i < current_size)
		{
			if (i > 0)
				printf(" ");
			printf("%d", current[i]);
			i++;
		}
		printf("\n");
		return ;
	}

	// Se já passou do alvo ou chegou ao fim, parar
	if (current_sum > target || index >= count)
		return ;

	// Para cada elemento restante
	i = index;
	while (i < count)
	{
		// Verificar se adicionar este número não excede o target
		if (current_sum + numbers[i] <= target)
		{
			// Adicionar o número ao subconjunto
			current[current_size] = numbers[i];
			// Chamar recursivamente para o próximo índice
			find_subsets(i + 1, current, current_size + 1,
				current_sum + numbers[i], target, numbers, count);
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	int target;
	int *numbers;
	int count;
	int *current;
	int i;

	// Precisa de pelo menos 2 argumentos (programa e target)
	if (argc < 2)
		return (1);

	// Converte o primeiro argumento para inteiro (target)
	target = atoi(argv[1]);

	// Número de elementos no conjunto
	count = argc - 2;

	// Se não há elementos no conjunto, é um erro
	if (count == 0)
		return (1);

	// Aloca array para os números
	numbers = malloc(count * sizeof(int));
	if (!numbers)
		return (1);

	// Aloca array para armazenar o subconjunto atual
	current = malloc(count * sizeof(int));
	if (!current)
	{
		free(numbers);
		return (1);
	}

	// Converte os argumentos para inteiros e armazena
	i = 0;
	while (i < count)
	{
		numbers[i] = atoi(argv[i + 2]);
		i++;
	}

	// Encontra todos os subconjuntos com soma = target
	find_subsets(0, current, 0, 0, target, numbers, count);

	// Libera memória
	free(numbers);
	free(current);
	return (0);
}
