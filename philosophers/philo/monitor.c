/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 23:03:05 by kyoshi            #+#    #+#             */
/*   Updated: 2026/01/18 02:32:19 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ============================================================================
 * FUNÇÃO: check_finished
 * Verifica se todos os filósofos já comeram o número mínimo de vezes
 * 
 * Parâmetros:
 *   table - Ponteiro para a estrutura da mesa
 * 
 * Retorno:
 *   1 se todos terminaram, 0 caso contrário
 * 
 * Observação:
 *   Esta verificação só é feita se must_eat > 0 (há um número mínimo)
 *   finished_count é incrementado em eat() quando um filósofo atinge o limite
 * ============================================================================ */
static int	check_finished(t_table *table)
{
	// Se há um número mínimo de refeições E todos os filósofos atingiram
	if (table->must_eat > 0 && table->finished_count >= table->n_philo)
	{
		table->stop = 1;  // Sinaliza parada da simulação
		return (1);       // Todos terminaram
	}
	return (0);  // Ainda há filósofos comendo
}

/* ============================================================================
 * FUNÇÃO: handle_death
 * Verifica e trata a morte de um filósofo
 * 
 * Parâmetros:
 *   table - Ponteiro para a estrutura da mesa
 *   philo - Ponteiro para o filósofo sendo verificado
 *   now   - Timestamp atual
 *   last  - Timestamp da última refeição do filósofo
 * 
 * Retorno:
 *   1 se o filósofo morreu, 0 caso contrário
 * 
 * Morte ocorre quando:
 *   (tempo atual - última refeição) > time_to_die
 * 
 * IMPORTANTE:
 *   - A mensagem de morte deve ser impressa em até 10ms da morte real
 *   - Usa dois mutexes para evitar race conditions:
 *     1. state_mutex: protege a flag stop
 *     2. print_mutex: garante que a mensagem não seja interrompida
 * ============================================================================ */
static int	handle_death(t_table *table, t_philo *philo, long long now,
long long last)
{
	// Verifica se passou do tempo limite sem comer
	if ((now - last) > table->time_die)
	{
		// Adquire mutex de estado para verificar/modificar stop
		pthread_mutex_lock(&table->state_mutex);
		// Verifica se a simulação já não foi parada (evita múltiplas mortes)
		if (!table->stop)
		{
			table->stop = 1;  // Sinaliza parada
			// Adquire mutex de impressão
			pthread_mutex_lock(&table->print_mutex);
			// Imprime mensagem de morte com timestamp relativo ao início
			printf("%lld %d died\n", now - table->start_time, philo->id);
			pthread_mutex_unlock(&table->print_mutex);
		}
		pthread_mutex_unlock(&table->state_mutex);
		return (1);  // Filósofo morreu
	}
	return (0);  // Filósofo ainda está vivo
}

/* ============================================================================
 * FUNÇÃO: check_philos
 * Verifica o estado de cada filósofo (se está vivo)
 * 
 * Parâmetros:
 *   philos - Array de filósofos
 * 
 * Retorno:
 *   1 se a simulação deve parar (morte ou já parada), 0 caso contrário
 * 
 * Processo:
 *   1. Obtém a mesa do primeiro filósofo
 *   2. Para cada filósofo:
 *      a. Verifica se a simulação já foi parada
 *      b. Lê o timestamp da última refeição (REGIÃO CRÍTICA)
 *      c. Obtém o timestamp atual
 *      d. Verifica se o filósofo morreu
 *   3. Retorna 1 se detectou morte, 0 se todos estão vivos
 * 
 * IMPORTANTE:
 *   O acesso a last_meal é protegido por state_mutex porque é modificado
 *   pela thread do filósofo em eat()
 * ============================================================================ */
static int	check_philos(t_philo *philos)
{
	t_table		*table;
	int			i;
	long long	now;
	long long	last;

	table = philos[0].table;  // Obtém referência à mesa
	i = 0;
	// Percorre todos os filósofos
	while (i < table->n_philo)
	{
		// Verifica se a simulação foi parada (REGIÃO CRÍTICA)
		pthread_mutex_lock(&table->state_mutex);
		if (table->stop)
		{
			pthread_mutex_unlock(&table->state_mutex);
			return (1);  // Simulação já foi parada
		}
		// Lê o timestamp da última refeição (REGIÃO CRÍTICA)
		last = philos[i].last_meal;
		pthread_mutex_unlock(&table->state_mutex);
		// Obtém timestamp atual
		now = get_time_ms();
		if (now == -1)
			return (1);  // Erro ao obter tempo
		// Verifica se este filósofo morreu
		if (handle_death(table, &philos[i], now, last))
			return (1);  // Filósofo morreu, para a simulação
		i++;
	}
	return (0);  // Todos estão vivos
}

/* ============================================================================
 * FUNÇÃO: monitor_routine
 * Rotina da thread de monitoramento
 * 
 * Parâmetros:
 *   arg - Ponteiro para o array de filósofos
 * 
 * Retorno:
 *   NULL (padrão de pthread)
 * 
 * Responsabilidades:
 *   1. Verificar constantemente se algum filósofo morreu
 *   2. Verificar se todos os filósofos atingiram o número mínimo de refeições
 *   3. Parar a simulação quando uma das condições acima for atendida
 * 
 * Loop principal:
 *   - Verifica todos os filósofos (detecta morte)
 *   - Verifica se todos terminaram de comer (se aplicável)
 *   - Dorme 500 microssegundos entre verificações (evita uso excessivo de CPU)
 * 
 * A thread termina quando:
 *   - Um filósofo morre
 *   - Todos os filósofos comeram o número mínimo de vezes
 * ============================================================================ */
void	*monitor_routine(void *arg)
{
	t_philo		*philos;
	t_table		*table;

	// Validação do argumento
	if (!arg)
		return (NULL);
	philos = (t_philo *)arg;
	table = philos[0].table;
	// Loop principal de monitoramento
	while (1)
	{
		// Verifica se algum filósofo morreu
		if (check_philos(philos))
			return (NULL);  // Morte detectada, encerra
		// Verifica se todos terminaram de comer (REGIÃO CRÍTICA)
		pthread_mutex_lock(&table->state_mutex);
		if (check_finished(table))
		{
			pthread_mutex_unlock(&table->state_mutex);
			return (NULL);  // Todos terminaram, encerra
		}
		pthread_mutex_unlock(&table->state_mutex);
		// Pequena pausa para não sobrecarregar a CPU
		// 500 microssegundos = 0.5 milissegundos
		usleep(500);
	}
	return (NULL);
}
