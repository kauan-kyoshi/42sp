/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_router.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:39 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:56:29 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

void	sort_stack(t_stack *stack)
{
	if (!stack || !stack->a || is_sorted(stack->a)) /* valida stack e verifica se já está ordenado */
		return ; /* se já está ordenado, encerra sem fazer nada (operações = 0) */
	if (stack->a->size == 2) /* se tamanho é 2 */
		sort_2(stack); /* chama sort_2 (algoritmo ótimo para 2) */
	else if (stack->a->size == 3) /* else se tamanho é 3 */
		sort_3(stack); /* chama sort_3 (algoritmo ótimo para 3) */
	else /* else tamanho > 3 */
		sort_many(stack); /* chama sort_many (casos 4, 5, e >5 com chunking ou radix) */
}
