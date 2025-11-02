/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:30:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/30 15:30:00 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	move_to_top_a(t_stack *stack, int position)
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
}


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

static void	move_smallest_to_b(t_stack *stack)
{
	int	min_value;
	int	position;

	min_value = find_min_value(stack->a);
	position = find_position(stack->a, min_value);
	move_to_top_a(stack, position);
	pb(stack, 1);
}

static int	find_position_in_a(t_stack *stack, int value)
{
	t_dnode	*current;
	int		pos;
	int		min_in_a;
	int		max_in_a;

	if (!stack->a || !stack->a->head)
		return (0);
	min_in_a = find_min_value(stack->a);
	max_in_a = find_max_value(stack->a);
	if (value < min_in_a || value > max_in_a)
		return (find_position(stack->a, min_in_a));
	current = stack->a->head;
	pos = 0;
	while (current && current->next)
	{
		if (get_value(current) < value && get_value(current->next) > value)
			return (pos + 1);
		current = current->next;
		pos++;
	}
	return (0);
}

static void	insert_back_to_a(t_stack *stack)
{
	int	value;
	int	position;

	while (stack->b && stack->b->head)
	{
		value = get_value(stack->b->head);
		position = find_position_in_a(stack, value);
		move_to_top_a(stack, position);
		pa(stack, 1);
	}
}

static void	final_position_a(t_stack *stack)
{
	int	min_value;
	int	position;

	min_value = find_min_value(stack->a);
	position = find_position(stack->a, min_value);
	move_to_top_a(stack, position);
}

void	sort_many(t_stack *stack)
{
	unsigned long	target_size;

	if (!stack || !stack->a)
		return ;
	target_size = 3;
	while (stack->a->size > target_size)
		move_smallest_to_b(stack);
	if (stack->a->size == 3)
		sort_3(stack);
	else if (stack->a->size == 2)
		sort_2(stack);
	insert_back_to_a(stack);
	final_position_a(stack);
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

