/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:18 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:48 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

static void	rotate_up(t_dlist *stack)
{
	t_dnode	*first; /* ponteiro para o primeiro nó a ser movido */

	if (!stack || !stack->head || stack->size < 2) /* valida se há pelo menos 2 elementos */
		return ; /* encerra se não há */
	first = stack->head; /* salva o primeiro nó */
	stack->head = first->next; /* novo head é o segundo nó */
	stack->head->prev = NULL; /* novo head não tem anterior */
	first->next = NULL; /* primeiro nó não tem próximo */
	first->prev = stack->tail; /* primeiro nó aponta para o antigo tail */
	stack->tail->next = first; /* antigo tail aponta para o primeiro nó */
	stack->tail = first; /* novo tail é o primeiro nó */
}

void	ra(t_stack *stack, int print)
{
	if (!stack || !stack->a || stack->a->size < 2) /* valida se A tem pelo menos 2 elementos */
		return ; /* encerra se não há */
	rotate_up(stack->a); /* rotaciona A para cima */
	if (print) /* se print = 1 */
		write(1, "ra\n", 3); /* imprime "ra" */
}

void	rb(t_stack *stack, int print)
{
	if (!stack || !stack->b || stack->b->size < 2) /* valida se B tem pelo menos 2 elementos */
		return ; /* encerra se não há */
	rotate_up(stack->b); /* rotaciona B para cima */
	if (print) /* se print = 1 */
		write(1, "rb\n", 3); /* imprime "rb" */
}

void	rr(t_stack *stack)
{
	ra(stack, 0); /* rotaciona A sem imprimir */
	rb(stack, 0); /* rotaciona B sem imprimir */
	write(1, "rr\n", 3); /* imprime "rr" uma única vez (representa ambas rotações) */
}
