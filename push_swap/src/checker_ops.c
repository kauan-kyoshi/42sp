/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:58:56 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:45:22 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui os protótipos, tipos (t_stack) e helpers usados neste arquivo */

int	apply_swap_ops(t_stack *stack, const char *op)
{
	/*
	verifica se a operação recebida é uma das operações de swap
	(sa, sb, ss). usa ft_strncmp para comparar os primeiros caracteres
	levando em conta o newline '\n' ou o terminador '\0'.
	Se corresponder, executa a operação correspondente sem imprimir
	(print = 0) e retorna 1 para indicar que a operação foi aplicada.
	*/
	if (!ft_strncmp(op, "sa\n", 3) || !ft_strncmp(op, "sa\0", 3))
		return (sa(stack, 0), 1); /* se for "sa" -> executa sa e retorna 1 */
	if (!ft_strncmp(op, "sb\n", 3) || !ft_strncmp(op, "sb\0", 3))
		return (sb(stack, 0), 1); /* se for "sb" -> executa sb e retorna 1 */
	if (!ft_strncmp(op, "ss\n", 3) || !ft_strncmp(op, "ss\0", 3))
		return (sa(stack, 0), sb(stack, 0), 1); /* se for "ss" -> executa sa e sb e retorna 1 */
	return (0); /* não correspondeu a nenhuma operação de swap */
}

int	apply_push_ops(t_stack *stack, const char *op)
{
	/*
	verifica e aplica operações de push (pa, pb).
	As operações são executadas com print = 0 (modo checker),
	e a função retorna 1 se aplicou alguma.
	*/
	if (!ft_strncmp(op, "pa\n", 3) || !ft_strncmp(op, "pa\0", 3))
		return (pa(stack, 0), 1); /* pa: move topo de B para A */
	if (!ft_strncmp(op, "pb\n", 3) || !ft_strncmp(op, "pb\0", 3))
		return (pb(stack, 0), 1); /* pb: move topo de A para B */
	return (0); /* nenhuma operação de push aplicada */
}

int	apply_rotate_ops(t_stack *stack, const char *op)
{
	/*
	verifica e aplica rotações para cima (ra, rb, rr).
	ra: rota A; rb: rota B; rr: rota A e B.
	*/
	if (!ft_strncmp(op, "ra\n", 3) || !ft_strncmp(op, "ra\0", 3))
		return (ra(stack, 0), 1); /* ra: rota a pilha A para cima */
	if (!ft_strncmp(op, "rb\n", 3) || !ft_strncmp(op, "rb\0", 3))
		return (rb(stack, 0), 1); /* rb: rota a pilha B para cima */
	if (!ft_strncmp(op, "rr\n", 3) || !ft_strncmp(op, "rr\0", 3))
		return (ra(stack, 0), rb(stack, 0), 1); /* rr: rota A e B */
	return (0); /* nenhuma rotação aplicada */
}

int	apply_rev_rotate_ops(t_stack *stack, const char *op)
{
	/*
	verifica e aplica rotações para baixo (rra, rrb, rrr).
	rra: rota A para baixo; rrb: rota B para baixo; rrr: ambos.
	Aqui usamos tamanho 4 na comparação porque as strings têm 3 letras + terminador/newline.
	*/
	if (!ft_strncmp(op, "rra\n", 4) || !ft_strncmp(op, "rra\0", 4))
		return (rra(stack, 0), 1); /* rra: rota a pilha A para baixo */
	if (!ft_strncmp(op, "rrb\n", 4) || !ft_strncmp(op, "rrb\0", 4))
		return (rrb(stack, 0), 1); /* rrb: rota a pilha B para baixo */
	if (!ft_strncmp(op, "rrr\n", 4) || !ft_strncmp(op, "rrr\0", 4))
		return (rra(stack, 0), rrb(stack, 0), 1); /* rrr: rra + rrb */
	return (0); /* nenhuma rev-rot aplicada */
}

int	apply_op(t_stack *stack, const char *op)
{
	/*
	Função central usada pelo checker: tenta aplicar a operação `op`
	chamando, em sequência, os grupos de operações: swap, push, rotate e rev-rotate.
	Retorna 1 se a operação foi reconhecida e aplicada, ou 0 caso contrário.
	*/
	if (!op)
		return (0); /* op nula -> nada a aplicar */
	if (apply_swap_ops(stack, op))
		return (1); /* se foi swap, já aplicou */
	if (apply_push_ops(stack, op))
		return (1); /* se foi push, já aplicou */
	if (apply_rotate_ops(stack, op))
		return (1); /* se foi rotate, já aplicou */
	if (apply_rev_rotate_ops(stack, op))
		return (1); /* se foi rev-rotate, já aplicou */
	return (0); /* operação desconhecida */
}
