#ifndef MINISHELL_H
# define MINISHELL_H

/* Feature test macro must be defined before any system headers in translation units
	that rely on POSIX definitions like struct sigaction. Defining it here ensures
	any source including this header gets the correct feature set. */
#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <signal.h>

/* Global flag set by the signal handler */
extern volatile sig_atomic_t g_last_signal;

/* Signal handler prototypes */
void sigint_handler(int sig);
void sigquit_handler(int sig);

int minishell_loop(void);

#endif
