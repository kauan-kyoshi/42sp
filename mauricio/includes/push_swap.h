/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 23:20:25 by mhidani           #+#    #+#             */
/*   Updated: 2025/10/08 14:03:13 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "dlist.h"

# define TRUE 0x01
# define FALSE 0x00

typedef char	t_bool;

typedef struct s_figure
{
	int		value;
	size_t	cost;
	t_bool	is_mediam;
}	t_figure;

typedef struct s_target
{
	t_dnode	*a;
	t_dnode	*b;
	size_t	best_cost;
}	t_target;

typedef struct s_sts_move
{
	t_bool	med_a;
	t_bool	med_b;
	size_t	cost_a;
	size_t	cost_b;
}	t_sts_move;

// Sort Algorithm ==============================================================
void		ft_stwo_nbrs(t_dlist **stk);
void		ft_sthree_nbrs(t_dlist **stk);
void		ft_sfive_nbrs(t_dlist **stk_a, t_dlist **stk_b);
void		ft_smany_nbrs(t_dlist **stk_a, t_dlist **stk_b);
// Handle Movement -------------------------------------------------------------
void		ft_handle_mmove(t_dlist **stk_a, t_dlist **stk_b, t_target *tgt);
void		ft_handle_move(t_dlist **stk, t_dnode *tgt, char *name);
// Cost ------------------------------------------------------------------------
void		ft_build_cost(t_dlist *stk);

// Utils =======================================================================
// Checkers Order --------------------------------------------------------------
t_bool		ft_is_ascending(t_dlist *stk);
t_bool		ft_is_descending(t_dlist *stk);
// Checkers end Builder --------------------------------------------------------
t_dlist		*ft_validate(int argc, char **argv);
t_bool		ft_validate_first(int argc, char **argv);
// Methods Element -------------------------------------------------------------
t_figure	*ft_figure(t_dnode *node);
void		ft_clean_figure(void *ptr);
t_dnode		*ft_find_min(t_dlist *stk, t_dnode *exc);
void		ft_find_best_target(t_dlist *stk_a, t_dlist *stk_b, t_target **tgt);

// Movements Operations ========================================================
void		ft_push(t_dlist **src, t_dlist **dst, char *dsp);
void		ft_swap(t_dlist **stk, char *dsp);
void		ft_swap_swap(t_dlist **stk_a, t_dlist **stk_b, char *dsp);
void		ft_rotate(t_dlist **stk, char *dsp);
void		ft_rotate_rotate(t_dlist **stk_a, t_dlist **stk_b, char *dsp);
void		ft_reverse_rotate(t_dlist **stk, char *dsp);
void		ft_reverse_rotate_rotate(t_dlist **a, t_dlist **b, char *dsp);

#endif
