/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:54 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:48 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

int	get_value(t_dnode *node)
{
	if (!node || !node->data) /* valida se o nó e seus dados existem */
		return (0); /* retorna 0 se nulo (valor padrão seguro) */
	return (*((int *)node->data)); /* desreferencia o ponteiro void* como int* e retorna seu valor */
}
