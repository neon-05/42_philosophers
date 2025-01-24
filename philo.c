#include "philo.h"

void	*philo(void *p)
{
	t_philo	*me;
	t_table	*table;

	me = p;
	table = me->table;
	// printf("[%li] h\n", me->id);
	pthread_mutex_lock(&(table->forks[me->id]));
	pthread_mutex_lock(&(table->forks[(me->id + 1) % table->nphilos]));
	printf("[%li] I am eating\n", me->id);
	usleep(table->tte);
	pthread_mutex_unlock(&(table->forks[me->id]));
	pthread_mutex_unlock(&(table->forks[(me->id + 1) % table->nphilos]));
	printf("[%li] I am done eating\n", me->id);
	usleep(table->tts);
	if (me->max_meals > 0 && --me->max_meals)
		philo(p);
	return (NULL);
}

int	main(void)
{
	size_t	i;
	t_philo	*philos;
	t_table	table;

	table.nphilos = 2;
	table.ttd = 5000000;
	table.tte = 500000;
	table.tts = 1000000;
	philos = malloc(sizeof(t_philo) * table.nphilos);
	table.forks = malloc(sizeof(pthread_mutex_t) * table.nphilos);
	i = 0;
	while (i < table.nphilos)
	{
		pthread_mutex_init(&(table.forks[i]), NULL);
		i++;
	}
	i = 0;
	while (i < table.nphilos)
	{
		philos[i].id = i;
		philos[i].table = &table;
		philos[i].max_meals = 8;
		pthread_create(&(philos[i].tid),NULL, &philo, &(philos[i]));
		i++;
	}
	i = 0;
	while (1)
	{
		pthread_join(philos[i].tid, NULL);
		i++;
		i%=table.nphilos;
	}
	return (0);
}
