/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:41:10 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/29 13:07:10 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_start_and_last_meal(t_table *table, t_philo *philos)
{
	int	i;

	/* registra instante inicial da simulacao e inicializa last_meal de cada filosofo */
	table->start_time = get_time_ms(); /* pega tempo em ms usado como referencia */
	if (table->start_time == -1)
		return (0); /* falha em obter tempo */
	i = 0;
	while (i < table->n_philo)
	{
		philos[i].last_meal = table->start_time; /* define ultima refeicao como inicio */
		i++;
	}
	return (1); /* sucesso */
}

static int	start_threads_and_monitor(t_table *table, t_philo *philos,
pthread_t *monitor)
{
	/* cria threads de filosofos e a thread monitor */
	if (create_thread(table, philos) != 0)
		return (0); /* falha ao criar threads de filosofos */
	if (pthread_create(monitor, NULL, monitor_routine, philos) != 0)
	{
		/* se monitor nao puder ser criado, sinaliza parada e aguarda join */
		table->stop = 1;
		join_threads(table, philos);
		return (0);
	}
	return (1); /* threads criadas com sucesso */
}

int	main(int argc, char **argv)
{
	t_args		args;
	t_table		table;
	t_philo		*philos;
	pthread_t	monitor;

	/* parse de argumentos de linha de comando */
	if (!parse_args(argc, argv, &args))
		return (1);
	/* inicializa estruturas de dados e mutexes */
	if (!init_table(&args, &table, &philos))
		return (1);
	/* marca tempo inicial e seta last_meal para todos filosofos */
	if (!set_start_and_last_meal(&table, philos))
	{
		destroy_table(&table, philos); /* limpa recursos em caso de erro */
		return (1);
	}
	/* cria threads e a thread monitor que observa terminacao/mortes */
	if (!start_threads_and_monitor(&table, philos, &monitor))
	{
		destroy_table(&table, philos);
		return (1);
	}
	/* aguarda monitor e filos terminarem, depois limpa recursos */
	pthread_join(monitor, NULL);
	join_threads(&table, philos);
	destroy_table(&table, philos);
	return (0);
}
