/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:56:21 by kyoshi            #+#    #+#             */
/*   Updated: 2026/01/18 02:19:51 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ============================================================================
 * FUNÇÃO: clean_init_part
 * Limpa recursos parcialmente inicializados em caso de erro durante a inicialização
 * 
 * Parâmetros:
 *   table         - Ponteiro para a estrutura da mesa
 *   forks_inited  - Número de mutexes de garfos que foram inicializados
 *   inited_flags  - Flags indicando quais mutexes foram inicializados
 *                   (bit 0 = print_mutex, bit 1 = state_mutex)
 *   philos        - Ponteiro para o array de filósofos (se já alocado)
 * ============================================================================ */
static void	clean_init_part(t_table *table, int forks_inited,
int inited_flags, t_philo *philos)
{
	int	i;

	// Destrói os mutexes dos garfos que foram inicializados
	if (table->forks)
	{
		i = 0;
		while (i < forks_inited)
		{
			pthread_mutex_destroy(&table->forks[i]);  // Destrói cada mutex
			i++;
		}
		free(table->forks);  // Libera a memória do array de mutexes
		table->forks = NULL;
	}
	// Destrói o mutex de impressão se foi inicializado (bit 0)
	if (inited_flags & 1)
		pthread_mutex_destroy(&table->print_mutex);
	// Destrói o mutex de estado se foi inicializado (bit 1)
	if (inited_flags & 2)
		pthread_mutex_destroy(&table->state_mutex);
	// Libera a memória dos filósofos se foi alocada
	if (philos)
		free(philos);
}

/* ============================================================================
 * FUNÇÃO: init_philos
 * Inicializa os dados de cada filósofo
 * 
 * Parâmetros:
 *   table  - Ponteiro para a estrutura da mesa
 *   philos - Array de filósofos a ser inicializado
 * 
 * Configurações:
 *   - ID: de 1 a n_philo (para exibição)
 *   - left: índice do garfo à esquerda (mesmo índice do filósofo)
 *   - right: índice do garfo à direita (próximo filósofo, circular)
 *   - meals: contador de refeições (inicia em 0)
 *   - last_meal: timestamp da última refeição (será definido no main)
 * ============================================================================ */
static void	init_philos(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		philos[i].id = i + 1;                           // ID começa em 1
		philos[i].left = i;                             // Garfo esquerdo
		philos[i].right = (i + 1) % table->n_philo;     // Garfo direito (circular)
		philos[i].meals = 0;                            // Ainda não comeu
		philos[i].last_meal = 0;                        // Será definido depois
		philos[i].thread = 0;                           // Thread ainda não criada
		philos[i].table = table;                        // Referência à mesa compartilhada
		i++;
	}
}

/* ============================================================================
 * FUNÇÃO: init_forks
 * Aloca e inicializa os mutexes dos garfos
 * 
 * Parâmetros:
 *   table - Ponteiro para a estrutura da mesa
 * 
 * Retorno:
 *   1 em caso de sucesso, 0 em caso de erro
 * 
 * Observação:
 *   Cada garfo é protegido por um mutex para evitar que dois filósofos
 *   peguem o mesmo garfo simultaneamente
 * ============================================================================ */
static int	init_forks(t_table *table)
{
	int	i;

	// Aloca memória para o array de mutexes (um para cada garfo)
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
		return (0);  // Falha na alocação
	i = 0;
	// Inicializa cada mutex
	while (i < table->n_philo)
	{
		// Tenta inicializar o mutex do garfo i
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			// Se falhar, limpa os mutexes já inicializados
			clean_init_part(table, i, 0, NULL);
			return (0);
		}
		i++;
	}
	return (1);  // Sucesso
}

/* ============================================================================
 * FUNÇÃO: init_mutexes
 * Inicializa todos os mutexes da mesa (garfos, impressão e estado)
 * 
 * Parâmetros:
 *   table - Ponteiro para a estrutura da mesa
 * 
 * Retorno:
 *   1 em caso de sucesso, 0 em caso de erro
 * ============================================================================ */
static int	init_mutexes(t_table *table)
{
	// Inicializa os mutexes dos garfos
	if (!init_forks(table))
		return (0);
	// Inicializa o mutex de impressão (para sincronizar os printf)
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		clean_init_part(table, table->n_philo, 0, NULL);
		return (0);
	}
	// Inicializa o mutex de estado (para proteger variáveis compartilhadas)
	if (pthread_mutex_init(&table->state_mutex, NULL) != 0)
	{
		clean_init_part(table, table->n_philo, 1, NULL);  // 1 = print_mutex já inicializado
		return (0);
	}
	return (1);  // Sucesso
}

/* ============================================================================
 * FUNÇÃO: init_table
 * Inicializa completamente a mesa e todos os filósofos
 * 
 * Parâmetros:
 *   args   - Estrutura com os argumentos parseados
 *   table  - Ponteiro para a estrutura da mesa a ser inicializada
 *   philos - Ponteiro duplo para o array de filósofos
 * 
 * Retorno:
 *   1 em caso de sucesso, 0 em caso de erro
 * 
 * Esta função:
 *   1. Copia os parâmetros de args para table
 *   2. Inicializa todos os mutexes
 *   3. Aloca memória para os filósofos
 *   4. Inicializa cada filósofo
 *   5. Define valores iniciais de controle
 * ============================================================================ */
int	init_table(t_args *args, t_table *table, t_philo **philos)
{
	// Validação de ponteiros
	if (!args || !table || !philos)
		return (0);
	// Copia os parâmetros dos argumentos para a mesa
	table->n_philo = args->n_philo;
	table->time_sleep = args->time_sleep;
	table->time_die = args->time_die;
	table->time_eat = args->time_eat;
	table->must_eat = args->must_eat;
	// Inicializa todos os mutexes (garfos, impressão e estado)
	if (!init_mutexes(table))
		return (0);
	// Aloca memória para o array de filósofos
	*philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!*philos)
	{
		clean_init_part(table, table->n_philo, 3, NULL);  // 3 = ambos mutexes inicializados
		return (0);
	}
	// Inicializa os dados de cada filósofo
	init_philos(table, *philos);
	// Define valores iniciais de controle
	table->start_time = 0;       // Será definido no main
	table->stop = 0;             // Simulação não parada
	table->finished_count = 0;   // Nenhum filósofo terminou ainda
	return (1);  // Sucesso
}
