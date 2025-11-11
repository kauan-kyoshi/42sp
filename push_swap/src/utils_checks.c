/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:48 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:48 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

int	has_duplicates(int *arr, int size)
{
	int	i; /* índice do loop externo */
	int	j; /* índice do loop interno (comparação) */

	i = 0; /* inicia primeiro índice */
	while (i < size) /* itera sobre cada elemento */
	{
		j = i + 1; /* começa a comparar com o próximo */
		while (j < size) /* compara com todos os posteriores */
		{
			if (arr[i] == arr[j]) /* se encontrou igualdade */
				return (1); /* retorna 1 (há duplicata) */
			j++; /* próximo índice */
		}
		i++; /* próximo elemento */
	}
	return (0); /* retorna 0 (sem duplicatas) */
}

int	is_sorted(t_dlist *stack)
{
	t_dnode	*current; /* ponteiro para iterar pela pilha */

	if (!stack || !stack->head || stack->size < 2) /* valida pilha e tamanho */
		return (1); /* pilha vazia ou com 1 elemento é sempre ordenada */
	current = stack->head; /* começa do primeiro nó */
	while (current && current->next) /* itera até o penúltimo nó */
	{
		if (get_value(current) > get_value(current->next)) /* se ordem crescente é violada */
			return (0); /* retorna 0 (não ordenado) */
		current = current->next; /* próximo nó */
	}
	return (1); /* retorna 1 (está ordenado) */
}
