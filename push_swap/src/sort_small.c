#include "../includes/push_swap.h"

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
