#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>


int main (void)
{
    printf("inicio\n");
    char *vector[2] = {"cat", NULL}; 
    int pid = fork();
    if (pid == 0)
    {
        int file = open("out", O_RDWR);
        int file2 = open("in", O_RDWR);
        dup2(file2,STDIN_FILENO);
        dup2(file,STDOUT_FILENO);
        close(file);
        close(file2);
        execve("/usr/bin/cat", vector, NULL);

    }
    waitpid(pid,NULL,0);
    printf("fim\n");
}