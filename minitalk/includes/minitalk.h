/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:16:05 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/12/05 13:43:07 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200809L
# endif

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdint.h>
# include "libft.h"

/*
 * Cabeçalho compartilhado do projeto minitalk.
 *
 * Objetivos deste header:
 * - fornecer includes portáveis e macros usadas tanto pelo cliente quanto
 *   pelo servidor (sinais, ACKs, etc.);
 * - declarar o tipo `t_state` usado para manter o estado do servidor que
 *   é acessado pelo signal handler; e funções utilitárias mínimas111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111.
 *
 * Observação sobre _POSIX_C_SOURCE: definimos 200809L para garantir a
 * disponibilidade de certas APIs POSIX (por exemplo getpid, sigaction,
 * usleep em algumas plataformas). Isso ajuda a tornar o código mais
 * portável entre ambientes Unix-like.
 */

/*
 * Estrutura de estado do servidor (`g_state` no código):
 * - `client_pid`: PID do cliente atualmente atendido (0 se nenhum).
 * - `current_char`: acumulador do byte que está sendo montado bit-a-bit.
 * - `bit_count`: quantos bits já foram recebidos para o `current_char`.
 *
 * NOTA sobre volatile sig_atomic_t:
 * - Estes campos são lidos e escritos no contexto de signal handlers. Para
 *   evitar comportamento indefinido e permitir acesso simples e seguro entre
 *   o handler e o fluxo principal, usamos `volatile sig_atomic_t`:
 *   - `sig_atomic_t` garante que leituras/escritas sejam feitas de forma
 *     atômica no nível da linguagem C em presença de sinais;
 *   - `volatile` impede otimizações que poderiam manter valores em
 *     registradores e fazer com que o código principal não veja atualizações
 *     feitas pelo handler.
 *
 * Limitação: operações compostas envolvendo múltiplos campos não são
 * atômicas; o design evita isso ou bloqueia sinais quando necessário.
 */
typedef struct s_state
{
	volatile sig_atomic_t    client_pid;
	volatile sig_atomic_t    current_char;
	volatile sig_atomic_t    bit_count;
}        t_state;


/*
 * Mapeamento de sinais para o protocolo:
 * - BIT_0 / BIT_1: sinais usados para transmitir um bit (0 ou 1) do
 *   cliente para o servidor. Aqui usamos sinais não-RT (SIGUSR1/SIGUSR2)
 *   por compatibilidade com as restrições do projeto.
 * - ACK_SIGNAL: sinal enviado pelo servidor para confirmar o processamento
 *   de cada bit (ACK por-bit). No código atual é mapeado para SIGUSR1.
 * - COMPLETE_ACK: sinal distinto enviado pelo servidor quando recebe o
 *   byte terminador '\0' indicando conclusão da mensagem; usamos sinal
 *   distinto para reduzir risco de coalescência (mapeado para SIGUSR2).
 */
# define BIT_0 SIGUSR1
# define BIT_1 SIGUSR2
# define ACK_SIGNAL SIGUSR1
# define COMPLETE_ACK SIGUSR2


/* re-declaração (opcional) de usleep para garantir assinatura visível */
int        usleep(useconds_t usec);

/* rotina utilitária simples para imprimir mensagem de erro e sair */
void    error_exit(char *msg, int code);

#endif
