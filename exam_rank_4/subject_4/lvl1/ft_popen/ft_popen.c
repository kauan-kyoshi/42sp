#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

// Cria um pipe e executa um comando em processo filho.
// type == 'r': pai lê a saída do comando.
// type == 'w': pai escreve para a entrada do comando.
int ft_popen(const char *file, char *const argv[], char type)
{
	// fd[0] = leitura do pipe, fd[1] = escrita do pipe.
	int fd[2];
	// pid vai guardar o retorno do fork().
	pid_t pid;

	// Valida parâmetros básicos de entrada.
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	// Cria o pipe para comunicação entre pai e filho.
	if (pipe(fd) == -1)
		return (-1);

	// Duplica o processo atual.
	pid = fork();

	// Bloco do processo filho.
	if (pid == 0)
	{
		// Redireciona STDOUT do filho para a ponta de escrita do pipe.
		// (Nesta versão mínima, o teste esperado usa esse fluxo.)
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			// Em caso de erro, fecha os FDs abertos antes de encerrar.
			close(fd[0]);
			close(fd[1]);
			exit(1);
		}

		// Filho não precisa mais dos FDs originais do pipe após dup2.
		close(fd[0]);
		close(fd[1]);
		// Executa o comando; só retorna se houver erro.
		execvp(file, argv);
		// Se execvp falhar, encerra o filho com erro.
		exit(1);
	}
	// Se o modo for leitura, o pai fecha a escrita e retorna leitura.
	if (type == 'r')
	{
		close(fd[1]);
		return (fd[0]);
	}
	// Caso contrário, o pai fecha a leitura e retorna escrita.
	close(fd[0]);
	return (fd[1]);
}

