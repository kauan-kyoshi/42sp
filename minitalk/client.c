#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Função para enviar um caractere bit a bit
void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		// Verifica o i-ésimo bit do caractere
		if ((c >> i) & 1)
			kill(pid, SIGUSR1); // Envia SIGUSR1 para o bit '1'
		else
			kill(pid, SIGUSR2); // Envia SIGUSR2 para o bit '0'
		usleep(100); // Pequena pausa para evitar sobrecarregar o servidor
		i--;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;
	int		i;

	// Validação dos argumentos
	if (argc != 3)
	{
		write(1, "Usage: ./client [server_pid] [message]\n", 40);
		return (1);
	}

	pid = atoi(argv[1]); // Converte o PID de string para inteiro
	message = argv[2];
	i = 0;

	// Envia cada caractere da mensagem
	while (message[i] != '\0')
	{
		send_char(pid, message[i]);
		i++;
	}

	// Envia o caractere nulo para indicar o fim da mensagem
	send_char(pid, '\0');

	return (0);
}