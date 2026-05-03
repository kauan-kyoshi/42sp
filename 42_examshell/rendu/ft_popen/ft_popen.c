#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int		fd[2];
	pid_t 	pid;

	if (!file || !argv || ( type != 'r' && type != 'w'))
		return -1;
	if (pipe(fd) == -1)
		return -1;
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1],STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execvp(file,argv);
	}
	if (type == 'r')
	{
		close(fd[1]);
		return fd[0];
	}
	close(fd[0]);
	return fd[1];
}