/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:41:10 by kyoshi            #+#    #+#             */
/*   Updated: 2026/01/18 02:19:51 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ============================================================================
 * FUNÇÃO: set_start_and_last_meal
 * Define o timestamp de início da simulação e a última refeição de cada filósofo
 * 
 * Parâmetros:
 *   table  - Ponteiro para a estrutura da mesa
 *   philos - Array de filósofos
 * 
 * Retorno:
 *   1 em caso de sucesso, 0 em caso de erro
 * 
 * Observação:
 *   Todos os filósofos começam com last_meal = start_time para evitar
 *   mortes imediatas no início da simulação
 * ============================================================================ */
static int	set_start_and_last_meal(t_table *table, t_philo *philos)
{
	int	i;

	// Obtém o timestamp atual como tempo de início
	table->start_time = get_time_ms();
	if (table->start_time == -1)
		return (0);  // Erro ao obter timestamp
	// Define o last_meal de cada filósofo como o tempo de início
	i = 0;
	while (i < table->n_philo)
	{
		philos[i].last_meal = table->start_time;
		i++;
	}
	return (1);  // Sucesso
}

/* ============================================================================
 * FUNÇÃO: start_threads_and_monitor
 * Cria as threads dos filósofos e a thread de monitoramento
 * 
 * Parâmetros:
 *   table   - Ponteiro para a estrutura da mesa
 *   philos  - Array de filósofos
 *   monitor - Ponteiro para a thread de monitoramento
 * 
 * Retorno:
 *   1 em caso de sucesso, 0 em caso de erro
 * 
 * Fluxo:
 *   1. Cria as threads de todos os filósofos
 *   2. Cria a thread de monitoramento
 *   3. Se algo falhar, para a simulação e aguarda as threads criadas
 * ============================================================================ */
static int	start_threads_and_monitor(t_table *table, t_philo *philos,
pthread_t *monitor)
{
	// Cria as threads de todos os filósofos
	if (create_thread(table, philos) != 0)
		return (0);  // Falha na criação das threads
	// Cria a thread de monitoramento
	if (pthread_create(monitor, NULL, monitor_routine, philos) != 0)
	{
		// Se falhar, sinaliza parada e aguarda as threads dos filósofos
		table->stop = 1;
		join_threads(table, philos);
		return (0);
	}
	return (1);  // Sucesso
}

/* ============================================================================
 * FUNÇÃO: main
 * Ponto de entrada do programa
 * 
 * Fluxo de execução:
 *   1. Faz o parse dos argumentos da linha de comando
 *   2. Inicializa a mesa e os filósofos
 *   3. Define o tempo de início e a última refeição
 *   4. Cria as threads dos filósofos e a thread de monitoramento
 *   5. Aguarda a thread de monitoramento terminar (fim da simulação)
 *   6. Aguarda todas as threads dos filósofos terminarem
 *   7. Libera recursos e finaliza
 * 
 * Retorno:
 *   0 em caso de sucesso, 1 em caso de erro
 * ============================================================================ */
int	main(int argc, char **argv)
{
	t_args		args;      // Argumentos parseados
	t_table		table;     // Mesa (recursos compartilhados)
	t_philo		*philos;   // Array de filósofos
	pthread_t	monitor;   // Thread de monitoramento

	// 1. Parse e validação dos argumentos
	if (!parse_args(argc, argv, &args))
		return (1);  // Argumentos inválidos
	// 2. Inicialização da mesa e filósofos
	if (!init_table(&args, &table, &philos))
		return (1);  // Falha na inicialização
	// 3. Define o tempo de início e última refeição
	if (!set_start_and_last_meal(&table, philos))
	{
		destroy_table(&table, philos);  // Limpa recursos antes de sair
		return (1);
	}
	// 4. Cria as threads
	if (!start_threads_and_monitor(&table, philos, &monitor))
	{
		destroy_table(&table, philos);  // Limpa recursos antes de sair
		return (1);
	}
	// 5. Aguarda o monitor terminar (detecta morte ou fim das refeições)
	pthread_join(monitor, NULL);
	// 6. Aguarda todas as threads dos filósofos terminarem
	join_threads(&table, philos);
	// 7. Libera todos os recursos (mutexes, memória)
	destroy_table(&table, philos);
	return (0);  // Sucesso
}
