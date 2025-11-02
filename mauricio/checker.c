/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:44:48 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/10 18:43:40 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_dlist	*ft_read_ops(void);
static char		*ft_get_op(t_dnode *p);
static t_bool	ft_vexc_op(t_dlist **stk_a, t_dlist **stk_b, t_dnode *p);
static void		ft_solve_ops(t_dlist **stk_a, t_dlist **stk_b, t_dlist **p);

int	main(int argc, char **argv)
{
	t_dlist	*stack_a;
	t_dlist	*stack_b;
	t_dlist	*operations;

	if (argc == 1)
		return (EXIT_SUCCESS);
	operations = ft_read_ops();
	stack_a = ft_validate(argc, argv);
	stack_b = ft_create_dlist(NULL);
	ft_solve_ops(&stack_a, &stack_b, &operations);
	if (ft_is_ascending(stack_a) == TRUE && stack_b->size == 0)
		ft_putstrln_fd("OK", STDOUT_FILENO);
	else
		ft_putstrln_fd("KO", STDOUT_FILENO);
	ft_clean_dlist(&stack_a, ft_clean_figure);
	ft_clean_dlist(&stack_b, ft_clean_figure);
	ft_clean_dlist(&operations, free);
	return (EXIT_SUCCESS);
}

static t_dlist	*ft_read_ops(void)
{
	t_dlist	*operations;
	char	*line;

	operations = ft_create_dlist(NULL);
	line = ft_get_next_line(STDIN_FILENO);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			break ;
		}
		ft_push_lst_dlist(operations, line);
		line = ft_get_next_line(STDIN_FILENO);
	}
	return (operations);
}

static char	*ft_get_op(t_dnode *p)
{
	if (!p)
		return (NULL);
	return ((char *)p->data);
}

static t_bool	ft_vexc_op(t_dlist **stk_a, t_dlist **stk_b, t_dnode *p)
{
	if (ft_strncmp(ft_get_op(p), "rra\n", 4) == 0)
		ft_reverse_rotate(stk_a, NULL);
	else if (ft_strncmp(ft_get_op(p), "rrb\n", 4) == 0)
		ft_reverse_rotate(stk_b, NULL);
	else if (ft_strncmp(ft_get_op(p), "rrr\n", 4) == 0)
		ft_reverse_rotate_rotate(stk_a, stk_b, NULL);
	else if (ft_strncmp(ft_get_op(p), "ra\n", 3) == 0)
		ft_rotate(stk_a, NULL);
	else if (ft_strncmp(ft_get_op(p), "rb\n", 3) == 0)
		ft_rotate(stk_b, NULL);
	else if (ft_strncmp(ft_get_op(p), "rr\n", 3) == 0)
		ft_rotate_rotate(stk_a, stk_b, NULL);
	else if (ft_strncmp(ft_get_op(p), "pa\n", 3) == 0)
		ft_push(stk_b, stk_a, NULL);
	else if (ft_strncmp(ft_get_op(p), "pb\n", 3) == 0)
		ft_push(stk_a, stk_b, NULL);
	else if (ft_strncmp(ft_get_op(p), "sa\n", 3) == 0)
		ft_swap(stk_a, NULL);
	else if (ft_strncmp(ft_get_op(p), "sb\n", 3) == 0)
		ft_swap(stk_b, NULL);
	else if (ft_strncmp(ft_get_op(p), "ss\n", 3) == 0)
		ft_swap_swap(stk_a, stk_b, NULL);
	else
		return (FALSE);
	return (TRUE);
}

static void	ft_solve_ops(t_dlist **stk_a, t_dlist **stk_b, t_dlist **opt)
{
	t_dnode	*pvt;

	pvt = (*opt)->head;
	while (pvt)
	{
		if (ft_vexc_op(stk_a, stk_b, pvt) == FALSE)
		{
			ft_clean_dlist(stk_a, ft_clean_figure);
			ft_clean_dlist(stk_b, ft_clean_figure);
			ft_clean_dlist(opt, free);
			ft_putstrln_fd("Error", STDOUT_FILENO);
			exit(EXIT_FAILURE);
		}
		pvt = pvt->next;
	}
}
