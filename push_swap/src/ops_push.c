/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:13 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:47 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

static void	push_from_to(t_dlist *from, t_dlist *to)
{
	int	*value_copy; /* ponteiro para cópia do valor do topo */

	if (!from || !to || !from->head) /* valida se há elementos a mover */
		return ; /* encerra se não há */
	if (!copy_top_value(from, &value_copy)) /* copia o valor do topo de `from` */
		return ; /* se falhou, encerra */
	detach_head_node(from); /* remove o nó do topo de `from` */
	push_value_to_dest(to, value_copy); /* adiciona a cópia ao topo de `to` */
}

void	pa(t_stack *stack, int print)
{
	if (!stack || !stack->b || !stack->b->head) /* valida se há elementos em B */
		return ; /* encerra se não há */
	push_from_to(stack->b, stack->a); /* move do topo de B para o topo de A */
	if (print) /* se print = 1 (modo push_swap) */
		write(1, "pa\n", 3); /* imprime "pa" */
}

void	pb(t_stack *stack, int print)
{
	if (!stack || !stack->a || !stack->a->head) /* valida se há elementos em A */
		return ; /* encerra se não há */
	push_from_to(stack->a, stack->b); /* move do topo de A para o topo de B */
	if (print) /* se print = 1 (modo push_swap) */
		write(1, "pb\n", 3); /* imprime "pb" */
}
