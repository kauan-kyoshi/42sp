/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_many.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:36 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:56:28 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

static void	move_to_top_b(t_stack *stack, int position)
{
	int		dist_top; /* distância até o topo */
	int		size; /* tamanho da pilha B */

	size = (int)stack->b->size; /* obtém o tamanho de B */
	if (position <= size / 2) /* se posição está na primeira metade */
	{
		dist_top = position; /* rotação é igual à posição */
		while (dist_top > 0) /* rota para cima `position` vezes */
		{
			rb(stack, 1); /* rota B para cima */
			dist_top--; /* decrementa contador */
		}
	}
	else /* senão está na segunda metade */
	{
		dist_top = size - position; /* rotação é tamanho - posição */
		while (dist_top > 0) /* rota para baixo `dist_top` vezes */
		{
			rrb(stack, 1); /* rota B para baixo */
			dist_top--; /* decrementa contador */
		}
	}
}

static void	phase_push_a_to_b(t_stack *stack, int chunk_size)
{
	int	pushed_count; /* contador de elementos já em B da primeira posição */

	pushed_count = 0; /* inicia em 0 */
	while (stack->a->size > 0) /* enquanto há elementos em A */
	{
		if (get_value(stack->a->head) <= pushed_count) /* se índice está entre 0 e pushed_count (menores já enviados) */
		{
			pb(stack, 1); /* envia para B */
			rb(stack, 1); /* rota B para cima (coloca menores no fundo) */
			pushed_count++; /* incrementa contador */
		}
		else if (get_value(stack->a->head) <= pushed_count + chunk_size) /* se índice está no chunk atual */
		{
			pb(stack, 1); /* envia para B */
			pushed_count++; /* incrementa contador (pronto para próximo chunk) */
		}
		else /* senão está fora do chunk */
			ra(stack, 1); /* rota A para cima (deixa para depois) */
	}
}

static void	phase_pull_b_to_a(t_stack *stack, int size)
{
	while (size > 0) /* enquanto há elementos para trazer */
	{
		move_to_top_b(stack, find_position(stack->b, size - 1)); /* traz o maior disponível (size-1) para o topo */
		pa(stack, 1); /* move para A */
		size--; /* decrementa (próximo a buscar) */
	}
}

static void	bring_min_to_top_and_pb(t_stack *stack)
{
	int pos; /* posição do elemento mínimo */
	int size; /* tamanho da pilha A */

	if (!stack || !stack->a) /* valida stack */
		return ; /* encerra se nulo */
	size = (int)stack->a->size; /* obtém tamanho de A */
	pos = find_position(stack->a, find_min_value(stack->a)); /* encontra posição do mínimo */
	if (pos <= size / 2) /* se mínimo está na primeira metade */
	{
		while (pos-- > 0) /* rota para cima `pos` vezes */
			ra(stack, 1); /* rota A para cima */
	}
	else /* senão está na segunda metade */
	{
		pos = size - pos; /* calcula rotação para baixo */
		while (pos-- > 0) /* rota para baixo `pos` vezes */
			rra(stack, 1); /* rota A para baixo */
	}
	pb(stack, 1); /* envia o mínimo para B */
}

void	sort_many(t_stack *stack)
{
	int		size; /* tamanho de A */
	int		chunks; /* número de chunks para chunking */
	int		chunk_size; /* tamanho de cada chunk */

	size = stack->a->size; /* obtém tamanho de A */
	if (size == 4) /* caso especial: 4 elementos */
	{
		bring_min_to_top_and_pb(stack); /* envia o menor para B */
		sort_3(stack); /* ordena os 3 restantes em A */
		pa(stack, 1); /* traz o menor de volta */
		return ; /* pronto */
	}
	if (size == 5) /* caso especial: 5 elementos */
	{
		bring_min_to_top_and_pb(stack); /* envia o menor para B */
		bring_min_to_top_and_pb(stack); /* envia o segundo menor para B */
		sort_3(stack); /* ordena os 3 restantes em A */
		pa(stack, 1); /* traz de volta um elemento */
		pa(stack, 1); /* traz de volta o outro elemento */
		return ; /* pronto */
	}
	if (size <= 100) /* se n <= 100, usa poucos chunks */
		chunks = 5; /* 5 chunks */
	else /* senão n > 100 */
		chunks = 11; /* 11 chunks */
	chunk_size = size / chunks; /* calcula tamanho de cada chunk (índices por chunk) */
	phase_push_a_to_b(stack, chunk_size); /* push todos de A para B por chunks */
	phase_pull_b_to_a(stack, size); /* pull de volta em ordem (maior primeiro) */
}
