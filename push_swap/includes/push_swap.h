/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/17 18:37:09 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "../libft/libft.h"

typedef struct s_stack
{
	t_dlist	*a;
	t_dlist	*b;
}	t_stack;

/* Parsing e validação */
int			parse_arguments(int argc, char **argv, t_stack *stack);
int			is_valid_number(char *str);
int			has_duplicates(int *arr, int size);
void		free_split(char **split);
long		ft_atol(const char *str);

/* Inicialização e limpeza */
t_stack		*init_stack(void);
void		free_stack(t_stack *stack);
void		free_int(void *data);

/* Operações básicas */
void		sa(t_stack *stack, int print);
void		sb(t_stack *stack, int print);
void		ss(t_stack *stack);
void		pa(t_stack *stack, int print);
void		pb(t_stack *stack, int print);
void		ra(t_stack *stack, int print);
void		rb(t_stack *stack, int print);
void		rr(t_stack *stack);
void		rra(t_stack *stack, int print);
void		rrb(t_stack *stack, int print);
void		rrr(t_stack *stack);

/* Funções auxiliares */
int			is_sorted(t_dlist *stack);
int			get_value(t_dnode *node);
int			find_min_value(t_dlist *stack);
int			find_max_value(t_dlist *stack);
int			find_position(t_dlist *stack, int value);
int			distance_to_top(t_dlist *stack, int position);

/* Algoritmos de ordenação */
void		sort_stack(t_stack *stack);
void		sort_2(t_stack *stack);
void		sort_3(t_stack *stack);
void		sort_many(t_stack *stack);

#endif