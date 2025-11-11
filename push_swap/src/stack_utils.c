/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:30:00 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:56:28 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

t_stack	*init_stack(void)
{
	t_stack	*stack; /* ponteiro para a estrutura das duas pilhas */

	stack = malloc(sizeof(t_stack)); /* aloca espaço para a estrutura t_stack */
	if (!stack) /* se malloc falhou */
		return (NULL); /* retorna nulo */
	stack->a = ft_create_dlist(NULL); /* cria pilha A vazia (dlist) */
	stack->b = ft_create_dlist(NULL); /* cria pilha B vazia (dlist) */
	if (!stack->a || !stack->b) /* se criação de alguma pilha falhou */
	{
		if (stack->a) /* se A foi criada */
			ft_clean_dlist(&stack->a, free_int); /* libera A */
		if (stack->b) /* se B foi criada */
			ft_clean_dlist(&stack->b, free_int); /* libera B */
		free(stack); /* libera a estrutura stack */
		return (NULL); /* retorna nulo */
	}
	return (stack); /* retorna a estrutura inicializada */
}

void	free_stack(t_stack *stack)
{
	if (!stack) /* valida se stack é nulo */
		return ; /* encerra sem fazer nada */
	if (stack->a) /* se pilha A existe */
		ft_clean_dlist(&stack->a, free_int); /* libera todos os nós e dados de A */
	if (stack->b) /* se pilha B existe */
		ft_clean_dlist(&stack->b, free_int); /* libera todos os nós e dados de B */
	free(stack); /* libera a estrutura stack em si */
}
