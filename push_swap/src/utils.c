/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:30:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/30 15:30:00 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			return (LONG_MAX);
		i++;
	}
	return (result * sign);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	has_duplicates(int *arr, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] == arr[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_int(void *data)
{
	free(data);
}

int	get_value(t_dnode *node)
{
	if (!node || !node->data)
		return (0);
	return (*((int *)node->data));
}

int	is_sorted(t_dlist *stack)
{
	t_dnode	*current;

	if (!stack || !stack->head || stack->size < 2)
		return (1);
	current = stack->head;
	while (current && current->next)
	{
		if (get_value(current) > get_value(current->next))
			return (0);
		current = current->next;
	}
	return (1);
}

int	find_min_value(t_dlist *stack)
{
	t_dnode	*current;
	int		min;

	if (!stack || !stack->head)
		return (0);
	min = get_value(stack->head);
	current = stack->head->next;
	while (current)
	{
		if (get_value(current) < min)
			min = get_value(current);
		current = current->next;
	}
	return (min);
}

int	find_max_value(t_dlist *stack)
{
	t_dnode	*current;
	int		max;

	if (!stack || !stack->head)
		return (0);
	max = get_value(stack->head);
	current = stack->head->next;
	while (current)
	{
		if (get_value(current) > max)
			max = get_value(current);
		current = current->next;
	}
	return (max);
}

int	find_position(t_dlist *stack, int value)
{
	t_dnode	*current;
	int		pos;

	if (!stack || !stack->head)
		return (-1);
	current = stack->head;
	pos = 0;
	while (current)
	{
		if (get_value(current) == value)
			return (pos);
		current = current->next;
		pos++;
	}
	return (-1);
}

int	distance_to_top(t_dlist *stack, int position)
{
	if (position < 0 || !stack)
		return (0);
	if (position <= (int)stack->size / 2)
		return (position);
	else
		return ((int)stack->size - position);
}

