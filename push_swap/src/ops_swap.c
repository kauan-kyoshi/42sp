/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:21 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:47 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

static void	swap_first_two(t_dlist *stack)
{
	t_dnode	*first; /* ponteiro para o primeiro nó */
	t_dnode	*second; /* ponteiro para o segundo nó */
	void	*temp_data; /* variável temporária para trocar dados */

	if (!stack || !stack->head || !stack->head->next) /* valida se há pelo menos 2 nós */
		return ; /* se não, encerra */
	first = stack->head; /* aponta para o primeiro nó */
	second = first->next; /* aponta para o segundo nó */
	temp_data = first->data; /* salva o dado do primeiro em temp */
	first->data = second->data; /* copia o dado do segundo para o primeiro */
	second->data = temp_data; /* copia temp (dado do primeiro) para o segundo */
}

void	sa(t_stack *stack, int print)
{
	if (!stack || !stack->a || stack->a->size < 2) /* valida se pilha A tem pelo menos 2 elementos */
		return ; /* encerra sem fazer nada */
	swap_first_two(stack->a); /* chama a função que troca os dois primeiros */
	if (print) /* se print = 1 (modo push_swap, não checker) */
		write(1, "sa\n", 3); /* imprime "sa" na saída padrão */
}

void	sb(t_stack *stack, int print)
{
	if (!stack || !stack->b || stack->b->size < 2) /* valida se pilha B tem pelo menos 2 elementos */
		return ; /* encerra sem fazer nada */
	swap_first_two(stack->b); /* chama a função que troca os dois primeiros de B */
	if (print) /* se print = 1 */
		write(1, "sb\n", 3); /* imprime "sb" */
}

void	ss(t_stack *stack)
{
	sa(stack, 0); /* executa sa sem imprimir */
	sb(stack, 0); /* executa sb sem imprimir */
	write(1, "ss\n", 3); /* imprime "ss" uma única vez (representa as duas operações) */
}
