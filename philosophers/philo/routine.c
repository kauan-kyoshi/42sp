/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 22:19:28 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/29 13:09:29 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	/* rotina padrao para um filosofo pegar dois garfos com estrategia anti-deadlock */
	if (philo->table->n_philo == 1)
	{
		/* caso especial: somente um garfo existe, pega-o e retorna (nao tenta pegar o segundo) */
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print_status(philo, "has taken a fork");
		return ;
	}
	/* strategy: alterna ordem de aquisicao entre filosofos pares e impares para evitar deadlock */
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->right]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->right]);
		print_status(philo, "has taken a fork");
	}
}

static void	eat(t_philo *philo)
{
	int	is_single; /* indica se ha apenas um filosofo na mesa */

	is_single = (philo->table->n_philo == 1);
	take_forks(philo); /* pega garfos (estrategia anti-deadlock incluida) */
	/* atualiza estado de ultimo tempo de refeicao e contador de refeicoes com protecao */
	pthread_mutex_lock(&philo->table->state_mutex);
	philo->last_meal = get_time_ms(); /* registra quando comecou a comer */
	philo->meals++; /* incrementa contador de refeicoes do filosofo */
	if (philo->table->must_eat > 0
		&& philo->meals == philo->table->must_eat)
		philo->table->finished_count++; /* conta filosofos que alcançaram objetivo */
	pthread_mutex_unlock(&philo->table->state_mutex);
	print_status(philo, "is eating"); /* log de inicio de comer */
	ft_usleep(philo->table->time_eat); /* simula tempo de comer */
	/* devolve os garfos apos comer; caso single libera apenas o garfo unico */
	if (is_single)
		pthread_mutex_unlock(&philo->table->forks[philo->left]);
	else
	{
		pthread_mutex_unlock(&philo->table->forks[philo->left]);
		pthread_mutex_unlock(&philo->table->forks[philo->right]);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	/* rotina principal executada por cada thread de filosofo */
	if (philo->table->n_philo == 1)
	{
		/* caso especial de 1 filosofo: pega um fork, espera ate morrer e libera */
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print_status(philo, "has taken a fork");
		ft_usleep(philo->table->time_die); /* nao pode comer, apenas espera morrer */
		pthread_mutex_unlock(&philo->table->forks[philo->left]);
		return (NULL);
	}
	/* pequena diferenca de inicio para reduzir contencao: impares dormem 1ms */
	if (philo->id % 2 == 1)
		ft_usleep(1);
	while (!sim_stopped(philo->table))
	{
		eat(philo); /* fase de comer */
		if (sim_stopped(philo->table))
			break ; /* checa novamente se simulacao foi parada */
		print_status(philo, "is sleeping"); /* fase de dormir */
		ft_usleep(philo->table->time_sleep);
		print_status(philo, "is thinking"); /* volta a pensar e repetir ciclo */
	}
	return (NULL);
}

int	create_thread(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philo_routine, &philos[i]) != 0)
		{
			/* em caso de falha na criacao de uma thread, aguarda as ja criadas */
			while (i-- > 0)
				pthread_join(philos[i].thread, NULL);
			return (1);
		}
		i++;
	}
	return (0); /* sucesso na criacao de todas threads */
}

void	join_threads(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_join(philos[i].thread, NULL); /* aguarda cada thread de filosofo terminar */
		i++;
	}
}
