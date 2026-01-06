/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 23:02:57 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/29 13:07:10 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_stopped(t_table *table)
{
	int	stopped; /* copia local do flag stop, lendo com protecao */

	pthread_mutex_lock(&table->state_mutex); /* protege acesso a table->stop */
	stopped = table->stop; /* le flag de parada */
	pthread_mutex_unlock(&table->state_mutex); /* liberta mutex de estado */
	return (stopped); /* retorna valor lido */
}

void	print_status(t_philo *philo, const char *msg)
{
	long long	now;

	/* evita imprimir estados apos a simulacao ser parada */
	pthread_mutex_lock(&philo->table->state_mutex); /* protege leitura de stop */
	if (philo->table->stop)
	{
		pthread_mutex_unlock(&philo->table->state_mutex); /* ja parado, nada a imprimir */
		return ;
	}
	/* garante que a impressao nao seja intercalada com outras */
	pthread_mutex_lock(&philo->table->print_mutex); /* toma mutex de impressao */
	now = get_time_ms() - philo->table->start_time; /* timestamp relativo desde o start */
	printf("%lld %d %s\n", now, philo->id, msg); /* imprime linha formatada exigida pelo enunciado */
	pthread_mutex_unlock(&philo->table->print_mutex); /* libera mutex de impressao */
	pthread_mutex_unlock(&philo->table->state_mutex); /* libera mutex de estado */
}
