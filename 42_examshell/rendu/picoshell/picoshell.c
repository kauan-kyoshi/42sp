#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int    picoshell(char **cmds[])
{
	int i=0;
	int fd[2];
	int pid;
	int prev_fd = -1;

	while (cmds[i])
	{
		if (cmds[i+1])
		{
			pipe(fd);
		}

		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != 1)
			{
				dup2(prev_fd,0);
				close(prev_fd);
			}

			if (cmds[i+1])
			{
				close(fd[0]);
				dup2(fd[1],1);
				close(fd[1]);
			}
			execvp(cmds[i][0],cmds[i]);
			exit(0);
		}

		if (prev_fd != -1)
		{
			close(prev_fd);
		}

		if (cmds[i+1])
		{
			close(fd[1]);
			prev_fd = fd[0];
			
		}
		i++;
	}
	return 0;
}