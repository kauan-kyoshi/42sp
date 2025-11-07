#include "../includes/push_swap.h"

int	ps_check_duplicates_in_stack(t_dlist *stack)
{
	t_dnode	*current;
	t_dnode	*compare;

	current = stack->head;
	while (current && current->next)
	{
		compare = current->next;
		while (compare)
		{
			if (get_value(current) == get_value(compare))
				return (1);
			compare = compare->next;
		}
		current = current->next;
	}
	return (0);
}
