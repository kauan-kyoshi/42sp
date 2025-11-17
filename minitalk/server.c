/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:53:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/17 17:48:49 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk.h" /* header com macros: BIT_0/BIT_1/ACK_SIGNAL/COMPLETE_ACK e typedefs */

/*
 * Estado global do servidor (acessado pelo handler).
 *
 * Estrutura t_state (definida em includes/minitalk.h) contém campos que são
 * atualizados diretamente no contexto do signal handler. Explicação dos
 * campos e por que eles são globais:
 * - client_pid: PID do cliente atualmente atendido. Mantemos o PID para
 *   poder enviar ACKs de volta ao remetente (kill(sender, ACK)).
 * - current_char: acumulador onde montamos o byte bit-a-bit. Deve ser
 *   tratado como unsigned para evitar comportamento indesejado em shifts.
 * - bit_count: quantos bits já foram recebidos para o byte atual (0..8).
 *
 * Razões para serem globais e acessíveis pelo handler:
 * - Um handler de sinal pode ser invocado a qualquer momento, interrompendo
 *   o fluxo principal; variáveis locais podem não estar em escopo/seguras.
 * - Usar campos globais de tipo sig_atomic_t (ou campos protegidos) é a
 *   abordagem padrão para compartilhar estado simples entre handler e main.
 */
static t_state	g_state = {0, 0, 0};


/*
 * process_full_byte
 * - É chamada quando 8 bits foram recebidos e o byte completo está pronto
 *   em g_state.current_char.
 * - A função executa apenas operações async-signal-safe: `write` e `kill`.
 * - Comportamento:
 *   - Se o byte reconstruído for '\0', tratamos como terminador de mensagem:
 *     escrevemos uma nova linha (separação) e enviamos COMPLETE_ACK ao
 *     cliente para confirmar a conclusão da mensagem. Em seguida liberamos
 *     o estado do client (client_pid = 0) para que outro cliente possa
 *     iniciar nova transmissão.
 *   - Caso contrário, convertemos `current_char` para `unsigned char` e
 *     escrevemos o byte no stdout via `write(1, &c, 1)`. Escrever byte-a-byte
 *     preserva sequências UTF-8 (transmitimos bytes crus).
 * - Após ler/processar o byte reiniciamos `current_char` e `bit_count`.
 */
static void	process_full_byte(pid_t sender)
{
	unsigned char	c; /* armazena o byte completo para escrita */

	if (g_state.current_char == 0) /* terminador de mensagem recebido */
	{
		/* separar visualmente mensagens no STDOUT */
		write(1, "\n", 1);
		/* ACK de conclusão: sinal distinto para evitar coalescência com ACKs por-bit */
		kill(sender, COMPLETE_ACK);
		/* libera estado para aceitar novo cliente */
		g_state.client_pid = 0;
	}
	else
	{
		/* convertendo para unsigned para imprimir byte cru corretamente */
		c = (unsigned char)g_state.current_char;
		write(1, &c, 1); /* async-signal-safe: imprime o byte recebido */
	}
	/* reset for next byte */
	g_state.current_char = 0;
	g_state.bit_count = 0;
}

/*
 * handler
 *
 * Signal handler com assinatura (int, siginfo_t *, void *). Foi registrado
 * com SA_SIGINFO para que possamos obter `info->si_pid` (o PID do remetente).
 *
 * Notas importantes sobre handlers de sinal:
 * - O handler deve usar apenas operações async-signal-safe (write, kill,
 *   atribuições atômicas em sig_atomic_t, etc.). Evite chamar funções como
 *   printf, malloc, fprintf, ou acessar estruturas complexas sem proteção.
 * - O parâmetro `ucontext` fornece o contexto de execução no momento do
 *   sinal (registradores, ponteiro de pilha, máscara de sinais). Neste
 *   projeto não precisamos dele; mantemos `(void)ucontext` para indicar
 *   intencionalmente que o parâmetro não é usado. Se precisássemos depurar
 *   ou manipular registradores, `ucontext` seria a ferramenta correta.
 *
 * Fluxo do handler:
 * 1) obtém o PID do remetente via `info->si_pid`.
 * 2) se não há cliente em atendimento (`client_pid == 0`), registra este
 *    sender como cliente atual.
 * 3) se outro cliente começar a enviar no meio da transmissão, resetamos
 *    o estado (current_char e bit_count) e trocamos o client_pid — isso
 *    garante que o servidor trate transmissões por cliente de forma
 *    sequencial e evita misturar bits de clientes diferentes.
 * 4) aplica o bit recebido ao acumulador `current_char` com shift-left e
 *    OR (MSB-first). Incrementa `bit_count`.
 * 5) quando chegam 8 bits, chama `process_full_byte` (que escreve/ack).
 * 6) envia um ACK por-bit (`kill(sender, ACK_SIGNAL)`) para autorizar o
 *    envio do próximo bit pelo cliente.
 *
 * Ordem do ACK: enviamos o ACK APÓS processar o bit/byte. Isso é importante
 * para evitar uma condição de corrida onde o cliente enviaria o próximo
 * bit antes do servidor ter atualizado seu estado interno.
 */
static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	pid_t	sender; /* PID do processo remetente obtido via siginfo */

	/* ucontext intencionalmente não usado aqui - ver comentários acima */
	(void)ucontext;
	/* obtém PID do cliente que enviou o sinal */
	sender = info->si_pid;

	/* se não estiver atendendo nenhum cliente, inicia atendimento */
	if (g_state.client_pid == 0)
		g_state.client_pid = sender;

	/* se um novo cliente começa a enviar enquanto outro estava em andamento,
	 * resetamos o estado e passamos a atender o novo remetente. Esta é uma
	 * estratégia simples que evita mesclar bits de clientes diferentes.
	 * Alternativamente, poderíamos enfileirar clientes, mas isso complica o
	 * handler e exige estruturas mais complexas (não-async-signal-safe). */
	if (sender != g_state.client_pid)
	{
		g_state.current_char = 0;
		g_state.bit_count = 0;
		g_state.client_pid = sender;
	}

	/* adiciona o bit recebido ao byte em construção (MSB-first) */
	if (sig == BIT_1)
		g_state.current_char = (g_state.current_char << 1) | 1;
	else
		g_state.current_char = (g_state.current_char << 1);

	g_state.bit_count++; /* um bit a mais recebido */

	/* se o byte estiver completo, processa-o (imprime/terminador) */
	if (g_state.bit_count == 8)
		process_full_byte(sender);

	/* ACK por-bit: autoriza o cliente a enviar o próximo bit */
	kill(sender, ACK_SIGNAL);
}

int	main(void)
{
	struct sigaction	sa; /* configurar handler com info do remetente */

	/*
	 * Registrar handler com SA_SIGINFO para receber siginfo_t (precisamos
	 * do PID do remetente em info->si_pid).
	 *
	 * A máscara `sa_mask` define sinais que serão bloqueados enquanto o
	 * handler estiver em execução — isso evita reentrância do handler e
	 * possíveis corrupções do estado global (por exemplo, dois handlers
	 * paralelos modificando g_state ao mesmo tempo).
	 */
	sa.sa_sigaction = handler; /* handler que recebe siginfo_t via sa_sigaction */
	sa.sa_flags = SA_SIGINFO; /* solicitar siginfo_t no handler */
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1); /* bloqueia SIGUSR1 dentro do handler */
	sigaddset(&sa.sa_mask, SIGUSR2); /* bloqueia SIGUSR2 dentro do handler */
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		write(1, "sigaction error\n", 17); /* erro ao registrar handler */
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		write(1, "sigaction error\n", 17);
	ft_printf("Server PID: %d\n", getpid()); /* imprime PID para que cliente saiba para onde enviar */
	while (1) /* servidor fica em loop infinito aguardando sinais */
		;
	return (0);
}
