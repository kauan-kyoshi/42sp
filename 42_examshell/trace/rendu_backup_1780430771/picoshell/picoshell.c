#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int    picoshell(char **cmds[])
{
	int fd[2];
	int i=0;
	int prev_fd = -1;
	int pid;

	while (cmds[i])
	{
		if (cmds[i+1])
		{
			pipe(fd);
		}
		pid = fork;
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd,0);
				close(fd);
			}

			if (cmds[i+1])
			{
				close(fd[0]);
				dup2(fd[1],1);
				close(fd[1]);
			}
			execvp(cmds[i][0],cmds[i]);
			exit(1);

		}
		if (prev_fd != -1 )
		{
			close(prev_fd);
		}



	}

}