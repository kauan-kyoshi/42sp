/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:56:21 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/29 13:07:10 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_init_part(t_table *table, int forks_inited,
int inited_flags, t_philo *philos)
{
	int	i; /* indice para destrucao parcial de forks caso de erro */

	if (table->forks)
	{
		i = 0;
		while (i < forks_inited)
		{
			pthread_mutex_destroy(&table->forks[i]); /* destroi somente os forks iniciados */
			i++;
		}
		free(table->forks); /* libera memoria do vetor */
		table->forks = NULL;
	}
	/* inited_flags usa bits para indicar quais mutexes foram inicializados */
	if (inited_flags & 1)
		pthread_mutex_destroy(&table->print_mutex); /* destroi print_mutex se inicializado */
	if (inited_flags & 2)
		pthread_mutex_destroy(&table->state_mutex); /* destroi state_mutex se inicializado */
	if (philos)
		free(philos); /* libera memoria dos filosofos se alocada */
}

static void	init_philos(t_table *table, t_philo *philos)
{
	int	i; /* indice para inicializar cada filosofo */

	i = 0;
	while (i < table->n_philo)
	{
		philos[i].id = i + 1; /* identificador humano-1 based */
		philos[i].left = i; /* indice do garfo a esquerda (proprio indice) */
		philos[i].right = (i + 1) % table->n_philo; /* garfo da direita (circular) */
		philos[i].meals = 0; /* contador de refeicoes comecando em 0 */
		philos[i].last_meal = 0; /* timestamp da ultima refeicao sera setado no start */
		philos[i].thread = 0; /* id da thread zerado antes de criar thread */
		philos[i].table = table; /* ponteiro para a tabela compartilhada */
		i++;
	}
}

static int	init_forks(t_table *table)
{
	int	i; /* indice para inicializacao de cada mutex de garfo */

	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo); /* aloca vetor de mutexes */
	if (!table->forks)
		return (0); /* falha de alocacao */
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			/* em caso de falha, destrói os mutexes já inicializados e libera */
			clean_init_part(table, i, 0, NULL);
			return (0);
		}
		i++;
	}
	return (1); /* sucesso */
}

static int	init_mutexes(t_table *table)
{
	/* inicializa todos os mutexes necessarios: forks e mutexes globais */
	if (!init_forks(table))
		return (0);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		/* se falhar, limpa forks iniciados */
		clean_init_part(table, table->n_philo, 0, NULL);
		return (0);
	}
	if (pthread_mutex_init(&table->state_mutex, NULL) != 0)
	{
		/* print_mutex ja foi inicializado, marca flag para destruicao */
		clean_init_part(table, table->n_philo, 1, NULL);
		return (0);
	}
	return (1); /* todos mutexes inicializados com sucesso */
}

int	init_table(t_args *args, t_table *table, t_philo **philos)
{
	if (!args || !table || !philos)
		return (0); /* argumentos invalidos -> falha */
	/* copia parametros parsed para estrutura compartilhada da tabela */
	table->n_philo = args->n_philo;
	table->time_sleep = args->time_sleep;
	table->time_die = args->time_die;
	table->time_eat = args->time_eat;
	table->must_eat = args->must_eat;
	/* inicializa mutexes e vetores compartilhados */
	if (!init_mutexes(table))
		return (0);
	/* aloca vetor de filosofos */
	*philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!*philos)
	{
		/* em caso de falha, limpa mutexes e forks */
		clean_init_part(table, table->n_philo, 3, NULL);
		return (0);
	}
	init_philos(table, *philos); /* inicializa cada entry do vetor de filosofos */
	table->start_time = 0; /* sera setado logo antes de spawn das threads */
	table->stop = 0; /* flag de parada da simulacao */
	table->finished_count = 0; /* contador de filosofos que ja comeram must_eat vezes */
	return (1); /* inicializacao completa */
}
