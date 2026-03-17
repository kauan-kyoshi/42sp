#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// Executa uma lista de comandos conectados por pipe.
int picoshell(char **cmds[])
{
	// Pipe atual: fd[0] leitura, fd[1] escrita.
	int fd[2];
	// Índice do comando atual dentro de cmds.
	int i = 0;
	// PID retornado por fork().
	int pid;
	// FD de leitura vindo do pipe anterior.
	int prev_fd = -1;

	// Percorre todos os comandos até encontrar NULL.
	while (cmds[i])
	{
		// Se existe próximo comando, precisa criar um novo pipe.
		if (cmds[i + 1])
		{
			// Cria pipe para ligar comando atual ao próximo.
			if (pipe(fd) == -1)
			{
				// Em erro, fecha FD anterior se existir.
				if (prev_fd != -1)
					close(prev_fd);
				// Retorna erro para o chamador.
				return (1);
			}
		}

		// Cria processo filho para executar o comando atual.
		pid = fork();

		// Bloco do filho.
		if (pid == 0)
		{
			// Se não é o primeiro comando, redireciona stdin.
			if (prev_fd != -1)
			{
				// stdin (0) passa a vir do pipe anterior.
				dup2(prev_fd, 0);
				// Fecha descritor antigo após dup2.
				close(prev_fd);
			}

			// Se existe próximo comando, redireciona stdout para pipe atual.
			if (cmds[i + 1])
			{
				// Filho não usa a ponta de leitura do pipe atual.
				close(fd[0]);
				// stdout (1) passa a escrever no pipe atual.
				dup2(fd[1], 1);
				// Fecha descritor antigo após dup2.
				close(fd[1]);
			}

			// Executa o comando (substitui o processo filho).
			execvp(cmds[i][0], cmds[i]);
			// Só chega aqui se execvp falhar.
			exit(1);
		}

		// No pai: fecha o pipe anterior, não é mais necessário.
		if (prev_fd != -1)
			close(prev_fd);

		// Prepara o próximo loop se houver próximo comando.
		if (cmds[i + 1])
		{
			// Pai não escreve no pipe atual.
			close(fd[1]);
			// Guarda leitura do pipe atual para virar entrada do próximo comando.
			prev_fd = fd[0];
		}

		// Avança para o próximo comando.
		i++;
	}
	// Retorno de sucesso (comportamento atual da sua versão).
	return (0);
}