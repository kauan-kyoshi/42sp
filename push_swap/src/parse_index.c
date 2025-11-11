/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:27 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:47 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

static void	bubble_sort(int *arr, int n)
{
	int	i; /* índice do loop externo (iterações completas) */
	int	j; /* índice do loop interno (comparações) */
	int	temp; /* variável temporária para trocar valores */

	i = 0; /* inicia primeira iteração */
	while (i < n - 1) /* executa n-1 passagens */
	{
		j = 0; /* reinicia índice interno para cada passagem */
		while (j < n - i - 1) /* compara até o ponto onde os maiores já estão no final */
		{
			if (arr[j] > arr[j + 1]) /* se o elemento atual é maior que o próximo */
			{
				temp = arr[j]; /* salva o elemento atual em temp */
				arr[j] = arr[j + 1]; /* copia o próximo para o atual */
				arr[j + 1] = temp; /* copia temp (o maior) para a próxima posição */
			}
			j++; /* próxima comparação */
		}
		i++; /* próxima passagem */
	}
}

static int	*build_sorted_array(t_dlist *a)
{
	int		*sorted_arr; /* array que conterá os valores ordenados */
	int		i; /* índice para preencher o array */
	t_dnode	*current; /* ponteiro para iterar pela pilha */

	sorted_arr = malloc(sizeof(int) * a->size); /* aloca array com tamanho igual ao da pilha */
	if (!sorted_arr) /* se malloc falhou */
		return (NULL); /* retorna nulo */
	current = a->head; /* começa pelo primeiro nó */
	i = 0; /* inicializa índice */
	while (current) /* itera por toda a pilha */
	{
		sorted_arr[i++] = get_value(current); /* copia valor do nó para o array e incrementa índice */
		current = current->next; /* próximo nó */
	}
	bubble_sort(sorted_arr, a->size); /* ordena o array usando bubble sort */
	return (sorted_arr); /* retorna o array ordenado */
}

static void	assign_indices(t_dlist *a, int *sorted_arr)
{
	t_dnode	*current; /* ponteiro para iterar pela pilha original */
	int		j; /* índice para procurar no array ordenado */

	current = a->head; /* começa pelo primeiro nó */
	while (current) /* itera por toda a pilha */
	{
		j = 0; /* reinicia índice de busca */
		while (j < (int)a->size) /* procura o valor de current no array ordenado */
		{
			if (get_value(current) == sorted_arr[j]) /* se encontrou correspondência */
			{
				*((int *)current->data) = j; /* substitui o valor original pelo índice (posição no array ordenado) */
				break ; /* sai do loop de busca */
			}
			j++; /* próxima posição no array ordenado */
		}
		current = current->next; /* próximo nó da pilha */
	}
}

void	ps_index_stack(t_stack *stack)
{
	int	*sorted_arr; /* array com valores ordenados */

	sorted_arr = build_sorted_array(stack->a); /* constrói o array ordenado */
	if (!sorted_arr) /* se falhou */
		return ; /* encerra sem fazer nada */
	assign_indices(stack->a, sorted_arr); /* atribui índices (0..n-1) aos nós baseado na posição no array */
	free(sorted_arr); /* libera o array temporário */
}
