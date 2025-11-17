/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:53:19 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/17 17:51:20 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ACK-enabled client: sends bits MSB-first and waits for server ack per bit.
 * BIT_0 = SIGUSR1, BIT_1 = SIGUSR2, ACK_SIGNAL = SIGUSR1
 */

#include "includes/minitalk.h" /* include do header do projeto com macros/definições */
#include <signal.h> /* para sigaction, kill, sig_atomic_t */
#include <unistd.h> /* para write, pause, usleep */
#include <sys/types.h> /* para pid_t */
#include <stdlib.h> /* para ft_atoi (via libft) e tipos */

/*
 * Contador global de ACKs recebidos do servidor.
 *
 * Por que sig_atomic_t + volatile?
 * - sig_atomic_t: garante operações de leitura/escrita atômicas do ponto de
 *   vista da linguagem C em presença de signal handlers. Isso evita que uma
 *   escrita parcial seja lida quando o handler modifica o valor.
 * - volatile: informa ao compilador que o valor pode mudar "de fora" do
 *   fluxo normal (p.ex. em um handler), então o compilador não deve otimizar
 *   técnicas como manter o valor em registrador ou remover leituras redundantes.
 *
 * Uso prático neste projeto:
 * - O handler do sinal incrementa `g_ack_count` quando um ACK chega.
 * - O loop de envio no fluxo principal lê esse contador para detectar a
 *   chegada de cada ACK e só prossegue quando o contador muda.
 */
static volatile sig_atomic_t	g_ack_count = 0;


/*
 * ack_handler
 * Handler simples invocado quando o cliente recebe um ACK do servidor.
 * Regras do handler:
 * - Fazer apenas operações async-signal-safe (incremento de sig_atomic_t é
 *   permitido). Evitar chamadas como printf, malloc, ou outras funções
 *   não reentrantes dentro do handler.
 * - Não depende do valor de `sig` aqui; apenas registra que um ACK ocorreu.
 */
static void	ack_handler(int sig)
{
	(void)sig; /* parâmetro intencionalmente não usado */
	g_ack_count++; /* sinaliza a chegada de mais um ACK ao fluxo principal */
}

/*
 * send_char
 *
 * Envia um byte inteiro para o servidor usando sinais, um por bit.
 * Detalhes e justificativas:
 * - Cada byte é transmitido MSB-first (bit 7 primeiro). Essa convenção
 *   simplifica a montagem no servidor (shift-left + OR) e é determinística.
 * - Por que enviar bit a bit com sinais?
 *   - Sinais UNIX (SIGUSR1/SIGUSR2) são o único mecanismo permitido pelo
 *     projeto (sem sockets/pipes). Enviar um byte inteiro por sinal não é
 *     viável; então mapeamos cada bit para um sinal.
 * - Sincronização por ACK:
 *   - Após enviar cada bit, o cliente espera por um ACK do servidor. Isso
 *     evita que o cliente envie bits mais rápido do que o servidor consegue
 *     processar (o kernel pode coalescer sinais iguais), o que poderia
 *     corromper a recepção.
 * - Uso de `unsigned char`:
 *   - Casting para `unsigned char` evita comportamento indefinido em
 *     plataformas onde `char` é signed e shifts aritméticos podem propagar
 *     o bit de sinal. Tratar bytes como unsigned garante manipulação correta
 *     dos bits 0..7.
 *
 * Implementação:
 * - `cur_count` guarda o valor atual de `g_ack_count` antes de enviar o
 *   sinal; o loop espera até que `g_ack_count` aumente (o handler de ACK faz
 *   o incremento) para garantir que o servidor processou o bit.
 * - `pause()` é usado para bloquear até a chegada do próximo sinal, reduzindo
 *   busy-wait e consumo de CPU.
 */
static int	send_char(pid_t server_pid, unsigned char c)
{
	int	cur_count; /* snapshot do contador de ACKs antes do envio do bit */
	int	i; /* índice do bit: 7..0 (MSB -> LSB) */

	i = 7;
	while (i >= 0)
	{
		cur_count = g_ack_count; /* marca o número atual de ACKs para detectar mudança */
		if (((c >> i) & 1) == 1) /* extrai o i-ésimo bit */
		{
			if (kill(server_pid, BIT_1) == -1) /* envia sinal para bit=1 */
				return (-1); /* erro ao enviar sinal */
		}
		else
		{
			if (kill(server_pid, BIT_0) == -1) /* envia sinal para bit=0 */
				return (-1);
		}
		/* espera até que o handler incremente g_ack_count */
		while (g_ack_count == cur_count)
			pause(); /* reativa quando qualquer sinal for entregue (espera pelo ACK) */
		i--; /* próximo bit */
	}
	return (0); /* byte enviado com sucesso */
}

/*
 * parse_args
 * - Valida argumentos de linha de comando e registra handlers para ACKs.
 *
 * Comportamento e detalhes técnicos:
 * - O cliente espera exatamente dois argumentos: PID do servidor e a
 *   mensagem a ser enviada. Usamos ft_atoi (libft) para converter o PID.
 * - Registramos dois handlers idênticos (ACK_SIGNAL e COMPLETE_ACK). O
 *   primeiro é usado como ACK por-bit; o segundo identifica a conclusão
 *   da mensagem. No cliente não precisamos de siginfo (quem enviou), apenas
 *   da notificação do ACK, por isso usamos sa_handler simples.
 * - Nota de robustez: se desejarmos distinguir tipos de ACK no handler,
 *   poderíamos registrar handlers diferentes ou usar SA_SIGINFO — aqui o
 *   código opta por simplicidade no cliente.
 */
static int	parse_args(int argc, char **argv, pid_t *server_pid)
{
	struct sigaction	sa; /* estrutura para registrar handler */

	/* validação de argumentos: programa, pid e mensagem */
	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	/* converter e validar PID do servidor */
	*server_pid = (pid_t)ft_atoi(argv[1]);
	if (*server_pid <= 0)
	{
		ft_printf("Invalid PID\n");
		return (1);
	}

	/* registrar handler simples para sinais de ACK.
	 * - Não precisamos de SA_SIGINFO no cliente porque apenas contamos ACKs.
	 * - O servidor é quem precisa do si_pid para identificar o remetente. */
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ack_handler; /* handler que incrementa g_ack_count */
	if (sigaction(ACK_SIGNAL, &sa, NULL) == -1)
		return (1);
	if (sigaction(COMPLETE_ACK, &sa, NULL) == -1)
		return (1);
	return (0);
}

/*
 * send_terminator_and_wait
 *
 * Envia o byte terminador '\0' que indica ao servidor o fim da mensagem e
 * aguarda a confirmação final.
 *
 * Por que aguardamos `prev + 9` ACKs?
 * - Quando enviamos o byte terminador, este byte gera 8 ACKs por-bit (um
 *   para cada bit enviado), igual ao envio de qualquer outro byte.
 * - Além desses 8 ACKs, o servidor envia um ACK de conclusão (COMPLETE_ACK)
 *   quando processa o byte '\0' e considera a mensagem concluída.
 * - Logo, esperamos por 9 incrementos no contador como sinal de sucesso.
 *
 * Timeout e robustez:
 * - Sinais não em tempo-real podem ser coalescidos pelo kernel se enviados
 *   muito próximos. Para evitar bloquear indefinidamente, implementamos um
 *   timeout aproximado (aqui ~2s, calculado como 2000 × 1ms). Se o tempo
 *   expirar, o cliente assume falha/ perda de ACK.
 */
static int	send_terminator_and_wait(pid_t server_pid)
{
	int	prev; /* contador de ACKs antes de enviar o terminador */
	int	waited; /* contador de timeout em milissegundos aproximados */

	prev = g_ack_count; /* snapshot do contador atual */
	if (send_char(server_pid, '\0') == -1) /* envia byte terminador */
		return (-1);
	waited = 0;
	/* espera pelos 8 ACKs dos bits + 1 ACK de conclusão, com timeout */
	while (g_ack_count < prev + 9 && waited < 2000)
	{
		usleep(1000); /* dorme 1ms para evitar busy-wait intenso */
		waited++;
	}
	if (g_ack_count >= prev + 9)
		ft_printf("Done\n"); /* recebeu a confirmação final */
	else
		ft_printf("No completion ACK (timeout)\n"); /* timeout: possível perda de sinal */
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid; /* PID do servidor para enviar sinais */
	size_t	i; /* índice para iterar sobre a C-string da mensagem */

	if (parse_args(argc, argv, &server_pid) != 0) /* valida e registra handlers */
		return (1);
	i = 0;
	while (argv[2][i]) /* percorre bytes da string até o NUL terminador */
	{
		if (send_char(server_pid, (unsigned char)argv[2][i]) == -1) /* envia cada byte como unsigned char */
		{
			ft_printf("Failed to send to server\n");
			return (1);
		}
		i++;
	}
	if (send_terminator_and_wait(server_pid) == -1) /* finaliza enviando '\0' e aguardando confirmacao */
	{
		ft_printf("Failed to send terminator\n");
		return (1);
	}
	return (0);
}
