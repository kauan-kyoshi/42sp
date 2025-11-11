/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rev_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:16 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:48 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

static void	rotate_down(t_dlist *stack)
{
	t_dnode	*last; /* ponteiro para o último nó a ser movido */

	if (!stack || !stack->tail || stack->size < 2) /* valida se há pelo menos 2 elementos */
		return ; /* encerra se não há */
	last = stack->tail; /* salva o último nó */
	stack->tail = last->prev; /* novo tail é o penúltimo nó */
	stack->tail->next = NULL; /* novo tail não tem próximo */
	last->prev = NULL; /* último nó não tem anterior */
	last->next = stack->head; /* último nó aponta para o antigo head */
	stack->head->prev = last; /* antigo head aponta para o último nó */
	stack->head = last; /* novo head é o último nó */
}

void	rra(t_stack *stack, int print)
{
	if (!stack || !stack->a || stack->a->size < 2) /* valida se A tem pelo menos 2 elementos */
		return ; /* encerra se não há */
	rotate_down(stack->a); /* rotaciona A para baixo */
	if (print) /* se print = 1 */
		write(1, "rra\n", 4); /* imprime "rra" */
}

void	rrb(t_stack *stack, int print)
{
	if (!stack || !stack->b || stack->b->size < 2) /* valida se B tem pelo menos 2 elementos */
		return ; /* encerra se não há */
	rotate_down(stack->b); /* rotaciona B para baixo */
	if (print) /* se print = 1 */
		write(1, "rrb\n", 4); /* imprime "rrb" */
}

void	rrr(t_stack *stack)
{
	rra(stack, 0); /* rotaciona A para baixo sem imprimir */
	rrb(stack, 0); /* rotaciona B para baixo sem imprimir */
	write(1, "rrr\n", 4); /* imprime "rrr" uma única vez (representa ambas rotações) */
}
