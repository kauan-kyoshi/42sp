/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 18:49:37 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/29 13:07:10 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_table(t_table *table, t_philo *philos)
{
	int		i; /* indice para iterar os forks */

	if (!table)
		return ; /* nada a limpar se tabela invalida */
	/* destroi mutexes de garfo e libera o vetor */
	if (table->forks)
	{
		i = 0;
		while (i < table->n_philo)
		{
			pthread_mutex_destroy(&table->forks[i]); /* destroi cada mutex do vetor */
			i++;
		}
		free(table->forks); /* libera memoria do vetor de forks */
		table->forks = NULL; /* evita dangling pointer */
	}
	/* destroi mutexes globais de log/estado */
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->state_mutex);
	/* libera array de filosofos alocado em init_table */
	if (philos)
		free(philos);
}
