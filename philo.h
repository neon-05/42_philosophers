#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

typedef struct s_table
{
	size_t			nphilos;
	pthread_mutex_t	*forks;
	unsigned long	ttd; // TimeToDie
	unsigned long	tte; // TimeToEat
	unsigned long	tts; // TimeToSleep
}	t_table;

typedef struct s_philo
{
	pthread_t		tid;
	size_t			id;
	t_table			*table;
	int				max_meals;
}	t_philo;
