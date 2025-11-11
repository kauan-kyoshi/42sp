/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pull_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:00:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 16:28:37 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
** move_to_top_b: Traz o elemento na posição 'position' de B para o topo.
** Escolhe a melhor rotação (rb ou rrb) baseado em qual é mais curta.
*/
void	move_to_top_b(t_stack *stack, int position)
{
	int		dist_top; /* distância a rotacionar */
	int		size; /* tamanho atual da pilha B */

	size = (int)stack->b->size; /* obtém tamanho de B */
	if (position <= size / 2) /* se posição está na primeira metade (mais perto do topo) */
	{
		dist_top = position; /* distância é exatamente a posição */
		while (dist_top > 0) /* enquanto houver distância a percorrer */
		{
			rb(stack, 1); /* rotaciona B para cima (move topo para base) */
			dist_top--; /* decrementa distância */
		}
	}
	else /* posição está na segunda metade (mais perto da base) */
	{
		dist_top = size - position; /* calcula distância da base para o elemento */
		while (dist_top > 0) /* enquanto houver distância a percorrer */
		{
			rrb(stack, 1); /* rotaciona B para baixo (move base para topo) */
			dist_top--; /* decrementa distância */
		}
	}
}

/*
** phase_pull_b_to_a: Segunda fase do algoritmo.
** Extrai todos os elementos de B e volta para A, começando pelo maior (size-1).
** Resultado: A fica completamente ordenado.
*/
void	phase_pull_b_to_a(t_stack *stack, int size)
{
	while (size > 0) /* para cada valor de size-1 até 0 */
	{
		/* encontra posição do elemento com valor = size-1 em B */
		move_to_top_b(stack, find_position(stack->b, size - 1));
		pa(stack, 1); /* move elemento do topo de B para o topo de A */
		size--; /* próximo valor a buscar e inserir */
	}
}