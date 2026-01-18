/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:23:19 by kyoshi            #+#    #+#             */
/*   Updated: 2026/01/18 02:19:51 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ============================================================================
 * FUNÇÃO: get_time_ms
 * Obtém o timestamp atual em milissegundos
 * 
 * Retorno:
 *   Timestamp em milissegundos desde a Unix Epoch (1 Jan 1970)
 *   -1 em caso de erro
 * 
 * Observação:
 *   Usa gettimeofday() que fornece precisão de microssegundos
 *   tv_sec: segundos desde a epoch
 *   tv_usec: microssegundos adicionais (0-999999)
 * ============================================================================ */
long long	get_time_ms(void)
{
	struct timeval	v;  // Estrutura que recebe tempo em segundos e microssegundos

	// Obtém o tempo atual
	if (gettimeofday(&v, NULL) == -1)
		return (-1);  // Erro ao obter tempo
	// Converte para milissegundos:
	// - v.tv_sec * 1000LL: converte segundos para milissegundos
	// - v.tv_usec / 1000: converte microssegundos para milissegundos
	return ((v.tv_sec * 1000LL) + (v.tv_usec / 1000));
}

/* ============================================================================
 * FUNÇÃO: ft_usleep
 * Implementação precisa de sleep em milissegundos
 * 
 * Parâmetros:
 *   ms - Tempo para dormir em milissegundos
 * 
 * Observação:
 *   Esta função é mais precisa que usleep() porque:
 *   1. Verifica constantemente o tempo decorrido
 *   2. Usa sleeps curtos quando está próximo do fim
 *   3. Evita drift de tempo acumulado
 * 
 *   Estratégia:
 *   - Se faltam mais de 5ms, dorme por (remaining - 1)ms
 *   - Se faltam 5ms ou menos, dorme apenas 100 microssegundos por vez
 *   - Isso evita oversleeping e mantém precisão
 * ============================================================================ */
void	ft_usleep(long long ms)
{
	long long	end;        // Timestamp quando deve acordar
	long long	now;        // Timestamp atual
	long long	remaining;  // Tempo restante para dormir

	// Se o tempo é zero ou negativo, não faz nada
	if (ms <= 0)
		return ;
	// Obtém o tempo atual
	now = get_time_ms();
	if (now == -1)
		return ;  // Erro ao obter tempo
	// Calcula quando deve acordar
	end = now + ms;
	// Loop até atingir o tempo desejado
	while (1)
	{
		// Obtém tempo atual
		now = get_time_ms();
		// Se houve erro ou já chegou no tempo, sai do loop
		if (now == -1 || now >= end)
			break ;
		// Calcula quanto tempo ainda falta
		remaining = end - now;
		// Se faltam mais de 5ms, pode dormir por mais tempo
		if (remaining > 5)
			usleep((remaining - 1) * 1000);  // Dorme por (remaining - 1)ms
		else
			usleep(100);  // Próximo do fim, dorme apenas 100 microssegundos
	}
}
