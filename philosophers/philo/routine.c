/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 22:19:28 by kyoshi            #+#    #+#             */
/*   Updated: 2026/01/18 02:20:04 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ============================================================================
 * FUNÇÃO: take_forks
 * O filósofo tenta pegar os dois garfos necessários para comer
 * 
 * Parâmetros:
 *   philo - Ponteiro para o filósofo
 * 
 * Estratégia para evitar deadlock:
 *   - Se há apenas 1 filósofo: pega um garfo e retorna (não pode comer)
 *   - Filósofos pares: pegam garfo DIREITO primeiro, depois ESQUERDO
 *   - Filósofos ímpares: pegam garfo ESQUERDO primeiro, depois DIREITO
 * 
 * Isso evita deadlock circular porque nem todos tentam pegar o mesmo
 * garfo ao mesmo tempo
 * ============================================================================ */
static void	take_forks(t_philo *philo)
{
	// Caso especial: apenas 1 filósofo
	// Ele pega um garfo mas nunca conseguirá pegar o segundo (não existe)
	if (philo->table->n_philo == 1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print_status(philo, "has taken a fork");
		return ;  // Não pode comer, vai esperar até morrer
	}
	// Filósofos pares pegam garfo direito primeiro
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->right]);  // Direito
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->left]);   // Esquerdo
		print_status(philo, "has taken a fork");
	}
	// Filósofos ímpares pegam garfo esquerdo primeiro
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->left]);   // Esquerdo
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->right]);  // Direito
		print_status(philo, "has taken a fork");
	}
}

/* ============================================================================
 * FUNÇÃO: eat
 * O filósofo come uma refeição
 * 
 * Parâmetros:
 *   philo - Ponteiro para o filósofo
 * 
 * Fluxo:
 *   1. Pega os dois garfos (ou um se for único filósofo)
 *   2. Atualiza last_meal e incrementa contador de refeições
 *   3. Verifica se atingiu o número necessário de refeições
 *   4. Imprime status "is eating"
 *   5. Dorme pelo tempo de comer
 *   6. Solta os garfos
 * 
 * IMPORTANTE: O mutex state_mutex protege as variáveis compartilhadas:
 *   - last_meal (usado pelo monitor para detectar morte)
 *   - meals (contador de refeições)
 *   - finished_count (número de filósofos que terminaram)
 * ============================================================================ */
static void	eat(t_philo *philo)
{
	int	is_single;

	is_single = (philo->table->n_philo == 1);
	// 1. Pega os garfos
	take_forks(philo);
	// 2. Atualiza informações da refeição (REGIÃO CRÍTICA)
	pthread_mutex_lock(&philo->table->state_mutex);
	philo->last_meal = get_time_ms();  // Atualiza timestamp da última refeição
	philo->meals++;                     // Incrementa contador de refeições
	// Se há um número mínimo de refeições e este filósofo alcançou
	if (philo->table->must_eat > 0
		&& philo->meals == philo->table->must_eat)
		philo->table->finished_count++;  // Incrementa contador de finalizados
	pthread_mutex_unlock(&philo->table->state_mutex);
	// 3. Imprime status e come
	print_status(philo, "is eating");
	ft_usleep(philo->table->time_eat);  // Dorme pelo tempo de comer
	// 4. Solta os garfos
	if (is_single)
		pthread_mutex_unlock(&philo->table->forks[philo->left]);
	else
	{
		pthread_mutex_unlock(&philo->table->forks[philo->left]);
		pthread_mutex_unlock(&philo->table->forks[philo->right]);
	}
}

/* ============================================================================
 * FUNÇÃO: philo_routine
 * Rotina principal executada por cada thread de filósofo
 * 
 * Parâmetros:
 *   arg - Ponteiro para a estrutura t_philo do filósofo
 * 
 * Retorno:
 *   NULL (padrão de pthread)
 * 
 * Ciclo de vida do filósofo:
 *   1. Se é único filósofo, apenas pega um garfo e espera morrer
 *   2. Filósofos ímpares esperam um pouco para dessincronizar
 *   3. Loop principal: comer → dormir → pensar
 *   4. Verifica se a simulação parou a cada iteração
 * 
 * Dessincronização:
 *   Filósofos ímpares esperam time_eat/2 antes de começar
 *   Isso evita que todos tentem pegar os garfos simultaneamente
 * ============================================================================ */
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;  // Cast do argumento
	// Caso especial: apenas 1 filósofo
	if (philo->table->n_philo == 1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print_status(philo, "has taken a fork");
		ft_usleep(philo->table->time_die);  // Espera até morrer
		pthread_mutex_unlock(&philo->table->forks[philo->left]);
		return (NULL);
	}
	// Dessincronização: filósofos ímpares esperam um pouco
	// Isso evita que todos tentem pegar garfos ao mesmo tempo
	if (philo->id % 2 == 1)
		ft_usleep(philo->table->time_eat / 2);
	// Loop principal: comer → dormir → pensar
	while (!sim_stopped(philo->table))
	{
		eat(philo);  // Come uma refeição
		// Verifica se a simulação parou (morte ou todos comeram)
		if (sim_stopped(philo->table))
			break ;
		// Dorme
		print_status(philo, "is sleeping");
		ft_usleep(philo->table->time_sleep);
		// Pensa
		print_status(philo, "is thinking");
	}
	return (NULL);
}

/* ============================================================================
 * FUNÇÃO: create_thread
 * Cria threads para todos os filósofos
 * 
 * Parâmetros:
 *   table  - Ponteiro para a estrutura da mesa
 *   philos - Array de filósofos
 * 
 * Retorno:
 *   0 em caso de sucesso, 1 em caso de erro
 * 
 * Em caso de erro:
 *   Aguarda todas as threads já criadas antes de retornar
 * ============================================================================ */
int	create_thread(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	// Cria uma thread para cada filósofo
	while (i < table->n_philo)
	{
		// Tenta criar a thread
		if (pthread_create(&philos[i].thread, NULL,
				philo_routine, &philos[i]) != 0)
		{
			// Se falhar, aguarda todas as threads já criadas
			while (i-- > 0)
				pthread_join(philos[i].thread, NULL);
			return (1);  // Erro
		}
		i++;
	}
	return (0);  // Sucesso
}

/* ============================================================================
 * FUNÇÃO: join_threads
 * Aguarda todas as threads dos filósofos terminarem
 * 
 * Parâmetros:
 *   table  - Ponteiro para a estrutura da mesa
 *   philos - Array de filósofos
 * ============================================================================ */
void	join_threads(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_join(philos[i].thread, NULL);  // Aguarda a thread i
		i++;
	}
}
