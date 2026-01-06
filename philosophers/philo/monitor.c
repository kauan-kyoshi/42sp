/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 23:03:05 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/29 13:09:40 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

static int	check_finished(t_table *table)
{
	/* verifica se condicao de parada por numero de refeicoes foi atingida */
	if (table->must_eat > 0 && table->finished_count >= table->n_philo)
	{
		table->stop = 1; /* sinaliza parada global */
		return (1); /* indica que simulacao terminou por count */
	}
	return (0); /* ainda nao terminou por esse criterio */
}

static int	handle_death(t_table *table, t_philo *philo, long long now,
long long last)
{
	/* determina se filo morreu por tempo sem comer */
	if ((now - last) > table->time_die)
	{
		/* bloqueia state_mutex para checar e atualizar stop de forma atomica */
		pthread_mutex_lock(&table->state_mutex);
		if (!table->stop)
		{
			table->stop = 1; /* marca simulacao como parada devido a morte */
			pthread_mutex_lock(&table->print_mutex); /* garante impressao exclusiva */
			printf("%lld %d died\n", now - table->start_time, philo->id); /* imprime morte */
			pthread_mutex_unlock(&table->print_mutex);
		}
		pthread_mutex_unlock(&table->state_mutex);
		return (1); /* sinaliza que houve uma morte */
	}
	return (0); /* sem morte detectada para esse filosofo */
}

static int	check_philos(t_philo *philos)
{
	 t_table	*table;
	 int		i;
	 long long	now;
	 long long	last;

	table = philos[0].table;
	i = 0;
	while (i < table->n_philo)
	{
		/* protege leitura do estado e do last_meal do filosofo */
		pthread_mutex_lock(&table->state_mutex);
		if (table->stop)
		{
			pthread_mutex_unlock(&table->state_mutex);
			return (1); /* simulacao ja parada -> encerra monitor */
		}
		last = philos[i].last_meal; /* leitura segura do ultimo tempo de refeicao */
		pthread_mutex_unlock(&table->state_mutex);
		now = get_time_ms(); /* pega tempo atual para comparar */
		if (now == -1)
			return (1); /* erro de tempo -> encerra monitor */
		if (handle_death(table, &philos[i], now, last))
			return (1); /* se houve morte, encerra monitor */
		i++;
	}
	return (0); /* nenhum evento que obrigue parada detectado */
}

void	*monitor_routine(void *arg)
{
	 t_philo	*philos;
	 t_table	*table;

	if (!arg)
		return (NULL);
	philos = (t_philo *)arg;
	table = philos[0].table;
	while (1)
	{
		/* varre filosofos procurando condicoes de parada (morte ou fim) */
		if (check_philos(philos))
			return (NULL);
		/* verifica se todos comeram o suficiente; protegemos a checagem por mutex */
		pthread_mutex_lock(&table->state_mutex);
		if (check_finished(table))
		{
			pthread_mutex_unlock(&table->state_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&table->state_mutex);
		usleep(500); /* pequeno atraso para reduzir carga do loop */
	}
	return (NULL);
}
