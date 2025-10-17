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

#include	<stdlib.h>
#include "../libft/libft.h"



typedef struct s_dnode
{
	void			*data;
	struct s_dnode	*next;
	struct s_dnode	*prev;
}	t_dnode;

typedef struct s_dlist
{
	struct s_dnode	*head;
	struct s_dnode	*tail;
	unsigned long	size;
}	t_dlist;


void push_swap(int argc, char **argv);
int *convert_arr(int argc, char **argv);
int *malloc_pile(int argc);
t_dlist *dlist_new(void);


#endif