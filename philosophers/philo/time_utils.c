/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshi <kyoshi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:23:19 by kyoshi            #+#    #+#             */
/*   Updated: 2025/12/29 13:07:09 by kyoshi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	v; /* estrutura para receber tempo do sistema em segundos + micros */

	if (gettimeofday(&v, NULL) == -1)
		return (-1); /* retorna -1 em caso de falha para sinalizar erro */
	return ((v.tv_sec * 1000LL) + (v.tv_usec / 1000)); /* converte tv para milissegundos e retorna */
}

void	ft_usleep(long long ms)
{
	long long	start; /* armazena timestamp inicial em ms */
	long long	now; /* timestamp atual em ms usado no loop */

	if (ms <= 0)
		return ; /* nada a fazer se tempo não for positivo */
	start = get_time_ms(); /* pega o tempo atual em ms */
	if (start == -1)
		return ; /* aborta em caso de erro ao obter tempo */
	while (1)
	{
		now = get_time_ms(); /* atualiza tempo corrente */
		if (now == -1)
			return ; /* aborta se não conseguiu obter tempo */
		if ((now - start) >= ms)
			break ; /* tempo desejado já passou; sai do loop */
		usleep(500); /* pequena pausa para evitar busy-wait intensa */
	}
}
