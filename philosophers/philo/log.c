/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 23:02:57 by kyoshi            #+#    #+#             */
/*   Updated: 2026/01/18 02:32:19 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ============================================================================
 * FUNÇÃO: sim_stopped
 * Verifica de forma thread-safe se a simulação foi parada
 * 
 * Parâmetros:
 *   table - Ponteiro para a estrutura da mesa
 * 
 * Retorno:
 *   1 se a simulação está parada, 0 se está rodando
 * 
 * Observação:
 *   Esta função é usada pelas threads dos filósofos para saber quando parar
 *   O acesso à variável stop é protegido por mutex para evitar race conditions
 * ============================================================================ */
int	sim_stopped(t_table *table)
{
	int	stopped;

	// Adquire o mutex de estado (REGIÃO CRÍTICA)
	pthread_mutex_lock(&table->state_mutex);
	stopped = table->stop;  // Lê o valor da flag
	pthread_mutex_unlock(&table->state_mutex);
	return (stopped);  // Retorna o valor lido
}

/* ============================================================================
 * FUNÇÃO: print_status
 * Imprime uma mensagem de status do filósofo de forma thread-safe
 * 
 * Parâmetros:
 *   philo - Ponteiro para o filósofo
 *   msg   - Mensagem a ser impressa
 * 
 * Formato da mensagem:
 *   timestamp_em_ms ID_do_filósofo mensagem
 * 
 * Exemplos:
 *   150 3 has taken a fork
 *   200 5 is eating
 *   300 1 is sleeping
 * 
 * IMPORTANTE - Sincronização:
 *   1. Primeiro verifica se a simulação está parada (com state_mutex)
 *   2. Se não estiver parada, adquire print_mutex ANTES de calcular timestamp
 *   3. Calcula timestamp e imprime (ambos protegidos por print_mutex)
 *   4. Libera print_mutex e depois state_mutex
 * 
 * Esta ordem de locks evita:
 *   - Mensagens misturadas (print_mutex)
 *   - Mensagens após a morte (verificação de stop)
 *   - Race conditions na leitura de stop (state_mutex)
 * ============================================================================ */
void	print_status(t_philo *philo, const char *msg)
{
	long long	now;

	// Adquire mutex de estado para verificar se deve parar
	pthread_mutex_lock(&philo->table->state_mutex);
	// Se a simulação já foi parada, não imprime nada
	if (philo->table->stop)
	{
		pthread_mutex_unlock(&philo->table->state_mutex);
		return ;
	}
	// Adquire mutex de impressão para garantir atomicidade
	// IMPORTANTE: mantém state_mutex locked para evitar race condition
	// onde stop poderia mudar entre a verificação e a impressão
	pthread_mutex_lock(&philo->table->print_mutex);
	// Calcula timestamp relativo ao início da simulação
	now = get_time_ms() - philo->table->start_time;
	// Imprime no formato: timestamp ID mensagem
	printf("%lld %d %s\n", now, philo->id, msg);
	// Libera mutex de impressão
	pthread_mutex_unlock(&philo->table->print_mutex);
	// Libera mutex de estado
	pthread_mutex_unlock(&philo->table->state_mutex);
}
