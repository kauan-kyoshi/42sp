/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:24 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:47 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

int	ps_check_duplicates_in_stack(t_dlist *stack)
{
	t_dnode	*current; /* ponteiro para iterar pelo primeiro nó comparado */
	t_dnode	*compare; /* ponteiro para iterar sobre nós subsequentes */

	current = stack->head; /* começa do primeiro nó da pilha */
	while (current && current->next) /* enquanto há pelo menos dois nós */
	{
		compare = current->next; /* começa a comparação com o próximo nó de current */
		while (compare) /* compara current com todos os nós que vêm após */
		{
			if (get_value(current) == get_value(compare)) /* se os valores são iguais */
				return (1); /* retorna 1 (há duplicata) */
			compare = compare->next; /* próximo nó para comparar */
		}
		current = current->next; /* próximo nó como referência */
	}
	return (0); /* retorna 0 (sem duplicatas encontradas) */
}
