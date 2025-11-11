/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:00:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 16:28:46 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
** bring_min_to_top_and_pb: Traz o menor elemento de A para o topo e o empurra para B.
** Escolhe rotação (ra/rra) baseado em qual caminho é mais curto.
*/
void	bring_min_to_top_and_pb(t_stack *stack)
{
	int	pos; /* posição do menor elemento em A */
	int	size; /* tamanho atual de A */

	if (!stack || !stack->a) /* validação: se stack ou stack->a é nulo */
		return ; /* sai da função */
	size = (int)stack->a->size; /* obtém tamanho de A */
	pos = find_position(stack->a, find_min_value(stack->a)); /* encontra posição do menor valor */
	if (pos <= size / 2) /* se o menor está na primeira metade (mais perto do topo) */
	{
		while (pos-- > 0) /* enquanto não chegou ao topo */
			ra(stack, 1); /* rotaciona A para cima */
	}
	else /* se o menor está na segunda metade (mais perto da base) */
	{
		pos = size - pos; /* calcula rotações necessárias da base para cima */
		while (pos-- > 0) /* enquanto não chegou ao topo */
			rra(stack, 1); /* rotaciona A para baixo */
	}
	pb(stack, 1); /* empurra o elemento mínimo do topo de A para B */
}

/*
** handle_small_cases: Trata casos especiais com 4 ou 5 elementos.
** Usa estratégia de extrair os menores para B, ordenar os restantes em A,
** e depois reinserir os extraídos.
*/
int	handle_small_cases(t_stack *stack, int size)
{
	if (size == 4) /* caso de 4 elementos */
	{
		bring_min_to_top_and_pb(stack); /* move o menor para B (restam 3 em A) */
		sort_3(stack); /* ordena os 3 restantes em A */
		pa(stack, 1); /* move de volta o elemento de B para A (no topo) */
		return (1); /* retorna sucesso */
	}
	if (size == 5) /* caso de 5 elementos */
	{
		bring_min_to_top_and_pb(stack); /* move o menor para B (restam 4 em A) */
		bring_min_to_top_and_pb(stack); /* move o segundo menor para B (restam 3 em A) */
		sort_3(stack); /* ordena os 3 restantes em A */
		pa(stack, 1); /* move primeiro elemento de B de volta para A */
		pa(stack, 1); /* move segundo elemento de B de volta para A */
		return (1); /* retorna sucesso */
	}
	return (0); /* não é caso pequeno, retorna falha */
}