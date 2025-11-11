/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:51 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 12:54:48 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h" /* inclui tipos e protótipos */

void	free_split(char **split)
{
	int	i; /* índice para iterar sobre o array de strings */

	if (!split) /* se split é nulo */
		return ; /* encerra sem fazer nada */
	i = 0; /* inicia índice */
	while (split[i]) /* enquanto há strings no array (até o terminador nulo) */
	{
		free(split[i]); /* libera cada string individualmente */
		i++; /* próxima string */
	}
	free(split); /* libera o array em si */
}

void	free_int(void *data)
{
	free(data); /* libera o ponteiro genérico (usado para dados void* dos nós) */
}
