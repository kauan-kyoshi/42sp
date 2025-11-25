#include "minishell.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t g_last_signal = 0;

void sigint_handler(int sig)
{
    g_last_signal = sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void sigquit_handler(int sig)
{
    (void)sig;
}

int main(void)
{
    char *line;

        
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("sigaction(SIGINT)");

    sa.sa_handler = sigquit_handler;
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        perror("sigaction(SIGQUIT)");


    while (1)
    {
        line = readline("minishell$ ");
        if (!line) 
            break;
        if (line[0] != '\0')
        {
            printf("%s\n",line);
            add_history(line);
        }

        if (strcmp(line, "ls") == 0)
            puts("mostra a lista do diretorio atual");

        free(line);
    }
    return 0;
}