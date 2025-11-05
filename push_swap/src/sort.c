/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:30:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/05 15:33:32 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
 * Algoritmo (implementação atual): estrategia por "chunks"/inserção.
 * 1) Distribui elementos de A para B em blocos (chunks) com base em limites
 *    para reduzir A a um núcleo pequeno.
 * 2) Ordena o núcleo (2–3 elementos) localmente e, em seguida, reinsere
 *    os elementos de B em A na posição correta, rotacionando quando
 *    necessário.
 */

/*static void	move_to_top_a(t_stack *stack, int position)
{
	int		dist_top;
	int		size;

	size = (int)stack->a->size;
	if (position <= size / 2)
	{
		dist_top = position;
		while (dist_top > 0)
		{
			ra(stack, 1);
			dist_top--;
		}
	}
	else
	{
		dist_top = size - position;
		while (dist_top > 0)
		{
			rra(stack, 1);
			dist_top--;
		}
	}
}*/


void	sort_2(t_stack *stack)
{
	if (!stack || !stack->a || stack->a->size != 2)
		return ;
	if (get_value(stack->a->head) > get_value(stack->a->head->next))
		sa(stack, 1);
}

void	sort_3(t_stack *stack)
{
	int	first;
	int	second;
	int	third;

	if (!stack || !stack->a || stack->a->size != 3)
		return ;
	first = get_value(stack->a->head);
	second = get_value(stack->a->head->next);
	third = get_value(stack->a->tail);
	if (first > second && second < third && first < third)
		sa(stack, 1);
	else if (first > second && second > third)
	{
		sa(stack, 1);
		rra(stack, 1);
	}
	else if (first > second && second < third && first > third)
		ra(stack, 1);
	else if (first < second && second > third && first < third)
	{
		sa(stack, 1);
		ra(stack, 1);
	}
	else if (first < second && second > third && first > third)
		rra(stack, 1);
}

static void	move_to_top_b(t_stack *stack, int position)
{
	int		dist_top;
	int		size;

	size = (int)stack->b->size;
	if (position <= size / 2)
	{
		dist_top = position;
		while (dist_top > 0)
		{
			rb(stack, 1);
			dist_top--;
		}
	}
	else
	{
		dist_top = size - position;
		while (dist_top > 0)
		{
			rrb(stack, 1);
			dist_top--;
		}
	}
}

void	sort_many(t_stack *stack)
{
	int	size;
	int	chunks;
	int	chunk_size;
	int	pushed_count;

	size = stack->a->size;
	if (size <= 100)
		chunks = 5;
	else
		chunks = 11;
	chunk_size = size / chunks;
	pushed_count = 0;
	while (stack->a->size > 0)
	{
		if (get_value(stack->a->head) <= pushed_count)
		{
			pb(stack, 1);
			rb(stack, 1);
			pushed_count++;
		}
		else if (get_value(stack->a->head) <= pushed_count + chunk_size)
		{
			pb(stack, 1);
			pushed_count++;
		}
		else
			ra(stack, 1);
	}
	while (size > 0)
	{
		move_to_top_b(stack, find_position(stack->b, size - 1));
		pa(stack, 1);
		size--;
	}
}

void	sort_stack(t_stack *stack)
{
	if (!stack || !stack->a || is_sorted(stack->a))
		return ;
	if (stack->a->size == 2)
		sort_2(stack);
	else if (stack->a->size == 3)
		sort_3(stack);
	else
		sort_many(stack);
}

