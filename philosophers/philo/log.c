#include "philo.h"

int	sim_stopped(t_table *table)
{
	int	stopped;

	pthread_mutex_lock(&table->state_mutex);
	stopped = table->stop;
	pthread_mutex_unlock(&table->state_mutex);
	return (stopped);
}

void	print_status(t_philo *philo, const char *msg)
{
	long	now;

	if (sim_stopped(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->print_mutex);
	if (!sim_stopped(philo->table))
	{
		now = get_time_ms() - philo->table->start_time;
		printf("%ld %d %s\n", now, philo->id+1,msg);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
}
