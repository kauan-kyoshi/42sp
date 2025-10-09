/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/09 17:46:25 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include	<stdlib.h>


typedef struct stack_a
{
	struct stack_a	*next;
	int				a;
}stack_a;

typedef struct stack_b
{
	struct stack_b	*next;
	int				b;
}stack_b;

#endif