/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:40:23 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/10 15:40:24 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Função para lidar com os sinais recebidos
void	handle_signal(int signum)
{
	static unsigned char	current_char = 0;
	static int				bit_count = 0;

	// Define o bit correspondente com base no sinal recebido
	if (signum == SIGUSR1)
		current_char |= (1 << (7 - bit_count)); // Define o bit como 1

	bit_count++;

	// Quando 8 bits forem recebidos, o caractere está completo
	if (bit_count == 8)
	{
		// Se o caractere for nulo, a string terminou
		if (current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &current_char, 1); // Imprime o caractere

		// Reseta para o próximo caractere
		bit_count = 0;
		current_char = 0;
	}
}

int	main(void)
{
	// Imprime o PID do servidor
	printf("Server PID: %d\n", getpid());

	// Configura os handlers para os sinais SIGUSR1 e SIGUSR2
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);

	// Loop infinito para manter o servidor em execução
	while (1)
		pause(); // Aguarda por um sinal

	return (0);
}