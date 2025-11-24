#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

static volatile sig_atomic_t g_last_signal = 0;

static void sigint_handler(int sig)
{
    (void)sig;
    g_last_signal = sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

static void sigquit_handler(int sig)
{
    (void)sig;
}

int main(void)
{
    char *line;

    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);

    while (1)
    {
        line = readline("minishell$ ");
        if (!line) 
            break;
        if (line[0] != '\0')
            add_history(line);

        if (strcmp(line, "ls") == 0)
            puts("mostra a lista do diretorio atual");

        free(line);
    }
    return 0;
}