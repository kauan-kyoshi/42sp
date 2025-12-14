#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct s_arg
{
	int n_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int must_eat;

}	t_args;


int parse_args(int argc, char **argv, t_args *args);


#endif