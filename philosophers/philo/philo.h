/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:31:40 by kyoshi            #+#    #+#             */
/*   Updated: 2026/01/18 02:19:51 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ============================================================================
 * INCLUDES
 * ============================================================================ */
# include <pthread.h>    // Para threads e mutexes (pthread_create, pthread_mutex_*)
# include <sys/time.h>   // Para gettimeofday (obter timestamp)
# include <unistd.h>     // Para usleep (pausar execução)
# include <stdio.h>      // Para printf (imprimir mensagens)
# include <stdlib.h>     // Para malloc e free (alocação de memória)
# include <string.h>     // Para funções de string (não usado ativamente)

/* ============================================================================
 * ESTRUTURA: t_table
 * Representa a "mesa" onde os filósofos estão sentados
 * Contém todos os recursos compartilhados e configurações da simulação
 * ============================================================================ */
typedef struct s_table
{
	pthread_mutex_t	*forks;         // Array de mutexes, um para cada garfo
	pthread_mutex_t	print_mutex;    // Mutex para sincronizar impressões (evitar misturar logs)
	pthread_mutex_t	state_mutex;    // Mutex para proteger variáveis de estado compartilhado
	long long		start_time;     // Timestamp do início da simulação (em ms)
	int				n_philo;        // Número total de filósofos
	int				time_die;       // Tempo máximo sem comer antes de morrer (em ms)
	int				time_eat;       // Tempo que leva para comer (em ms)
	int				time_sleep;     // Tempo que leva para dormir (em ms)
	int				must_eat;       // Número de vezes que cada filósofo deve comer (-1 = sem limite)
	int				stop;           // Flag: 1 = simulação parada, 0 = em execução
	int				finished_count; // Contador de filósofos que terminaram de comer
}	t_table;

/* ============================================================================
 * ESTRUTURA: t_philo
 * Representa um filósofo individual
 * Cada filósofo é uma thread separada
 * ============================================================================ */
typedef struct s_philo
{
	int			id;         // ID do filósofo (de 1 a n_philo)
	int			left;       // Índice do garfo da esquerda
	int			right;      // Índice do garfo da direita
	int			meals;      // Número de refeições já consumidas
	long long	last_meal;  // Timestamp da última refeição (em ms)
	pthread_t	thread;     // Thread do filósofo
	t_table		*table;     // Ponteiro para a mesa (recursos compartilhados)
}	t_philo;

/* ============================================================================
 * ESTRUTURA: t_args
 * Armazena os argumentos parseados da linha de comando
 * ============================================================================ */
typedef struct s_arg
{
	int	n_philo;     // Número de filósofos
	int	time_die;    // Tempo para morrer (ms)
	int	time_eat;    // Tempo para comer (ms)
	int	time_sleep;  // Tempo para dormir (ms)
	int	must_eat;    // Número mínimo de refeições (-1 se não especificado)
}	t_args;

/* ============================================================================
 * FUNÇÕES: Parsing de argumentos (args.c)
 * ============================================================================ */
// Faz o parse e validação dos argumentos da linha de comando
int			parse_args(int argc, char **argv, t_args *args);

/* ============================================================================
 * FUNÇÕES: Utilitários de tempo (time_utils.c)
 * ============================================================================ */
// Retorna o tempo atual em milissegundos
long long	get_time_ms(void);
// Pausa a execução por ms milissegundos de forma precisa
void		ft_usleep(long long ms);

/* ============================================================================
 * FUNÇÕES: Inicialização e limpeza (init.c, cleanup.c)
 * ============================================================================ */
// Inicializa a mesa e os filósofos
int			init_table(t_args *args, t_table *table, t_philo **philos);
// Destrói mutexes e libera memória
void		destroy_table(t_table *table, t_philo *philos);

/* ============================================================================
 * FUNÇÕES: Threads e rotinas (routine.c, monitor.c)
 * ============================================================================ */
// Cria as threads dos filósofos
int			create_thread(t_table *table, t_philo *philos);
// Aguarda todas as threads de filósofos terminarem
void		join_threads(t_table *table, t_philo *philos);
// Rotina principal de cada filósofo (comer, dormir, pensar)
void		*philo_routine(void *arg);
// Rotina de monitoramento (detecta morte e fim da simulação)
void		*monitor_routine(void *arg);

/* ============================================================================
 * FUNÇÕES: Logging e controle (log.c)
 * ============================================================================ */
// Verifica se a simulação foi parada
int			sim_stopped(t_table *table);
// Imprime uma mensagem de status do filósofo
void		print_status(t_philo *philo, const char *msg);

#endif