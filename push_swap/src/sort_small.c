/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:42 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:56:28 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

void	sort_2(t_stack *stack)
{
	if (!stack || !stack->a || stack->a->size != 2) /* valida se há exatamente 2 elementos */
		return ; /* encerra se não */
	if (get_value(stack->a->head) > get_value(stack->a->head->next)) /* se primeiro > segundo */
		sa(stack, 1); /* troca os dois (primeira operação > segunda ordena) */
}

void	sort_3(t_stack *stack)
{
	int	first; /* valor do primeiro nó */
	int	second; /* valor do segundo nó */
	int	third; /* valor do terceiro nó (tail) */

	if (!stack || !stack->a || stack->a->size != 3) /* valida se há exatamente 3 elementos */
		return ; /* encerra se não */
	first = get_value(stack->a->head); /* obtém primeiro valor */
	second = get_value(stack->a->head->next); /* obtém segundo valor */
	third = get_value(stack->a->tail); /* obtém terceiro valor */
	/* agora trata os 5 casos possíveis de desordenação com 3 elementos: */
	if (first > second && second < third && first < third) /* 2 1 3 */
		sa(stack, 1); /* basta trocar os dois primeiros */
	else if (first > second && second > third) /* 3 2 1 */
	{
		sa(stack, 1); /* primeiro: troca (torna 2 3 1) */
		rra(stack, 1); /* depois rota para baixo (torna 1 2 3) */
	}
	else if (first > second && second < third && first > third) /* 3 1 2 */
		ra(stack, 1); /* rota para cima (torna 1 2 3) */
	else if (first < second && second > third && first < third) /* 1 3 2 */
	{
		sa(stack, 1); /* troca (torna 3 1 2) */
		ra(stack, 1); /* rota (torna 1 2 3) */
	}
	else if (first < second && second > third && first > third) /* 2 3 1 */
		rra(stack, 1); /* rota para baixo (torna 1 2 3) */
	/* caso restante: 1 2 3 (já ordenado) — não faz nada */
}
