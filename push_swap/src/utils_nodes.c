#include "../includes/push_swap.h"

int	get_value(t_dnode *node)
{
	if (!node || !node->data)
		return (0);
	return (*((int *)node->data));
}
