/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:32:48 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/08 13:30:36 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_begin_step(int c, char **v, t_dlist **stk_a, t_dlist **stk_b);

int	main(int argc, char **argv)
{
	t_dlist	*stack_a;
	t_dlist	*stack_b;

	ft_begin_step(argc, argv, &stack_a, &stack_b);
	if (ft_is_ascending(stack_a))
	{
		ft_clean_dlist(&stack_a, ft_clean_figure);
		ft_clean_dlist(&stack_b, ft_clean_figure);
		return (EXIT_SUCCESS);
	}
	if (stack_a->size == 2)
		ft_stwo_nbrs(&stack_a);
	if (stack_a->size == 3)
		ft_sthree_nbrs(&stack_a);
	if (stack_a->size == 5)
		ft_sfive_nbrs(&stack_a, &stack_b);
	else
		ft_smany_nbrs(&stack_a, &stack_b);
	ft_clean_dlist(&stack_a, ft_clean_figure);
	ft_clean_dlist(&stack_b, ft_clean_figure);
	return (EXIT_SUCCESS);
}

static void	ft_begin_step(int c, char **v, t_dlist **stk_a, t_dlist **stk_b)
{
	if (c < 2)
		exit(EXIT_SUCCESS);
	*stk_a = ft_validate(c, v);
	if (!*stk_a)
	{
		ft_putstrln_fd("Error", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	*stk_b = ft_create_dlist(NULL);
	if (!*stk_b)
	{
		ft_putstrln_fd("Error", STDOUT_FILENO);
		ft_clean_dlist(stk_a, ft_clean_figure);
		exit(EXIT_FAILURE);
	}
}
