/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 18:49:37 by kyoshi            #+#    #+#             */
/*   Updated: 2026/01/18 02:32:19 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ============================================================================
 * FUNÇÃO: destroy_table
 * Libera todos os recursos alocados (mutexes e memória)
 * 
 * Parâmetros:
 *   table  - Ponteiro para a estrutura da mesa
 *   philos - Ponteiro para o array de filósofos
 * 
 * Recursos liberados:
 *   1. Todos os mutexes dos garfos
 *   2. Memória do array de mutexes dos garfos
 *   3. Mutex de impressão (print_mutex)
 *   4. Mutex de estado (state_mutex)
 *   5. Memória do array de filósofos
 * 
 * Observação:
 *   Esta função deve ser chamada apenas após todas as threads terem terminado
 *   (após join_threads) para evitar destruir mutexes que ainda estão em uso
 * ============================================================================ */
void	destroy_table(t_table *table, t_philo *philos)
{
	int		i;

	// Validação do ponteiro da mesa
	if (!table)
		return ;
	// Destrói os mutexes dos garfos e libera a memória
	if (table->forks)
	{
		i = 0;
		// Destrói cada mutex de garfo
		while (i < table->n_philo)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		// Libera a memória do array de mutexes
		free(table->forks);
		table->forks = NULL;  // Boa prática: evita dangling pointer
	}
	// Destrói o mutex de impressão
	pthread_mutex_destroy(&table->print_mutex);
	// Destrói o mutex de estado
	pthread_mutex_destroy(&table->state_mutex);
	// Libera a memória do array de filósofos
	if (philos)
		free(philos);
}
