/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:30:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/30 15:30:00 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	swap_first_two(t_dlist *stack)
{
	t_dnode	*first;
	t_dnode	*second;
	void	*temp_data;

	if (!stack || !stack->head || !stack->head->next)
		return ;
	first = stack->head;
	second = first->next;
	temp_data = first->data;
	first->data = second->data;
	second->data = temp_data;
}

void	sa(t_stack *stack, int print)
{
	if (!stack || !stack->a || stack->a->size < 2)
		return ;
	swap_first_two(stack->a);
	if (print)
		write(1, "sa\n", 3);
}

void	sb(t_stack *stack, int print)
{
	if (!stack || !stack->b || stack->b->size < 2)
		return ;
	swap_first_two(stack->b);
	if (print)
		write(1, "sb\n", 3);
}

void	ss(t_stack *stack)
{
	sa(stack, 0);
	sb(stack, 0);
	write(1, "ss\n", 3);
}

static void	push_from_to(t_dlist *from, t_dlist *to)
{
	t_dnode	*node_to_move;
	void	*data;
	int		*value_copy;

	if (!from || !to || !from->head)
		return ;
	node_to_move = from->head;
	data = node_to_move->data;
	value_copy = malloc(sizeof(int));
	if (!value_copy)
		return ;
	*value_copy = *((int *)data);
	if (from->head == from->tail)
	{
		from->head = NULL;
		from->tail = NULL;
		from->size = 0;
	}
	else
	{
		from->head = from->head->next;
		if (from->head)
			from->head->prev = NULL;
		from->size--;
	}
	free_int(node_to_move->data);
	free(node_to_move);
	if (to->head == NULL)
	{
		to->head = ft_create_dnode(value_copy);
		to->tail = to->head;
		to->size = 1;
	}
	else
	{
		ft_push_beg_dlist(to, value_copy);
	}
}

void	pa(t_stack *stack, int print)
{
	if (!stack || !stack->b || !stack->b->head)
		return ;
	push_from_to(stack->b, stack->a);
	if (print)
		write(1, "pa\n", 3);
}

void	pb(t_stack *stack, int print)
{
	if (!stack || !stack->a || !stack->a->head)
		return ;
	push_from_to(stack->a, stack->b);
	if (print)
		write(1, "pb\n", 3);
}

static void	rotate_up(t_dlist *stack)
{
	t_dnode	*first;

	if (!stack || !stack->head || stack->size < 2)
		return ;
	first = stack->head;
	stack->head = first->next;
	stack->head->prev = NULL;
	first->next = NULL;
	first->prev = stack->tail;
	stack->tail->next = first;
	stack->tail = first;
}

void	ra(t_stack *stack, int print)
{
	if (!stack || !stack->a || stack->a->size < 2)
		return ;
	rotate_up(stack->a);
	if (print)
		write(1, "ra\n", 3);
}

void	rb(t_stack *stack, int print)
{
	if (!stack || !stack->b || stack->b->size < 2)
		return ;
	rotate_up(stack->b);
	if (print)
		write(1, "rb\n", 3);
}

void	rr(t_stack *stack)
{
	ra(stack, 0);
	rb(stack, 0);
	write(1, "rr\n", 3);
}

static void	rotate_down(t_dlist *stack)
{
	t_dnode	*last;

	if (!stack || !stack->tail || stack->size < 2)
		return ;
	last = stack->tail;
	stack->tail = last->prev;
	stack->tail->next = NULL;
	last->prev = NULL;
	last->next = stack->head;
	stack->head->prev = last;
	stack->head = last;
}

void	rra(t_stack *stack, int print)
{
	if (!stack || !stack->a || stack->a->size < 2)
		return ;
	rotate_down(stack->a);
	if (print)
		write(1, "rra\n", 4);
}

void	rrb(t_stack *stack, int print)
{
	if (!stack || !stack->b || stack->b->size < 2)
		return ;
	rotate_down(stack->b);
	if (print)
		write(1, "rrb\n", 4);
}

void	rrr(t_stack *stack)
{
	rra(stack, 0);
	rrb(stack, 0);
	write(1, "rrr\n", 4);
}

