/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:00:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:56:28 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

int	find_min_value(t_dlist *stack)
{
	t_dnode	*current; /* ponteiro para iterar pela pilha */
	int		min; /* armazena o valor mínimo encontrado */

	if (!stack || !stack->head) /* valida se a pilha existe e não está vazia */
		return (0); /* retorna 0 se vazia */
	min = get_value(stack->head); /* inicia min com o primeiro valor */
	current = stack->head->next; /* começa a iterar a partir do segundo */
	while (current) /* itera por todos os nós restantes */
	{
		if (get_value(current) < min) /* se encontrou valor menor */
			min = get_value(current); /* atualiza min */
		current = current->next; /* próximo nó */
	}
	return (min); /* retorna o valor mínimo encontrado */
}

int	find_max_value(t_dlist *stack)
{
	t_dnode	*current; /* ponteiro para iterar pela pilha */
	int		max; /* armazena o valor máximo encontrado */

	if (!stack || !stack->head) /* valida se a pilha existe e não está vazia */
		return (0); /* retorna 0 se vazia */
	max = get_value(stack->head); /* inicia max com o primeiro valor */
	current = stack->head->next; /* começa a iterar a partir do segundo */
	while (current) /* itera por todos os nós restantes */
	{
		if (get_value(current) > max) /* se encontrou valor maior */
			max = get_value(current); /* atualiza max */
		current = current->next; /* próximo nó */
	}
	return (max); /* retorna o valor máximo encontrado */
}

int	find_position(t_dlist *stack, int value)
{
	t_dnode	*current; /* ponteiro para iterar pela pilha */
	int		pos; /* armazena a posição (índice) do nó */

	if (!stack || !stack->head) /* valida se a pilha existe e não está vazia */
		return (-1); /* retorna -1 se não encontrável */
	current = stack->head; /* começa do primeiro nó */
	pos = 0; /* inicia posição em 0 */
	while (current) /* itera por todos os nós */
	{
		if (get_value(current) == value) /* se encontrou o valor */
			return (pos); /* retorna a posição */
		current = current->next; /* próximo nó */
		pos++; /* incrementa posição */
	}
	return (-1); /* retorna -1 se não encontrou */
}

int	distance_to_top(t_dlist *stack, int position)
{
	if (position < 0 || !stack) /* valida posição e pilha */
		return (0); /* retorna 0 se inválido */
	if (position <= (int)stack->size / 2) /* se posição está na primeira metade */
		return (position); /* distância é a posição mesma (usar ra) */
	else /* senão está na segunda metade */
		return ((int)stack->size - position); /* distância é tamanho - posição (usar rra) */
}
