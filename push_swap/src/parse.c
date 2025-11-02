/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:30:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/30 15:30:00 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static int	process_single_arg(char *arg, t_stack *stack)
{
	char	**split;
	int		i;
	long	num;
	int		*value;

	split = ft_split(arg, ' ');
	if (!split)
		return (0);
	i = 0;
	while (split[i])
	{
		if (!is_valid_number(split[i]))
		{
			free_split(split);
			return (0);
		}
		num = ft_atol(split[i]);
		if (num > INT_MAX || num < INT_MIN)
		{
			free_split(split);
			return (0);
		}
		value = malloc(sizeof(int));
		if (!value)
		{
			free_split(split);
			return (0);
		}
		*value = (int)num;
		ft_push_lst_dlist(stack->a, value);
		i++;
	}
	free_split(split);
	return (1);
}

static int	check_duplicates_in_stack(t_dlist *stack)
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

int	parse_arguments(int argc, char **argv, t_stack *stack)
{
	int		i;
	long	num;
	int		*value;

	if (argc < 2)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (count_words(argv[i], ' ') > 1)
		{
			if (!process_single_arg(argv[i], stack))
				return (0);
		}
		else
		{
			if (!is_valid_number(argv[i]))
				return (0);
			num = ft_atol(argv[i]);
			if (num > INT_MAX || num < INT_MIN)
				return (0);
			value = malloc(sizeof(int));
			if (!value)
				return (0);
			*value = (int)num;
			ft_push_lst_dlist(stack->a, value);
		}
		i++;
	}
	if (check_duplicates_in_stack(stack->a))
		return (0);
	return (1);
}

