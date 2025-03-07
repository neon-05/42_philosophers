/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:22:30 by ylabussi          #+#    #+#             */
/*   Updated: 2025/03/07 16:19:28 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	size_t			n_philo;
	pthread_mutex_t	*forks;
	long			ttd;
	long			tte;
	long			tts;
	int				max_meals;
	size_t			deadphilo;
	pthread_mutex_t	deadphilo_lock;
	struct timeval	start;
}	t_table;

typedef struct s_philo
{
	pthread_t		tid;
	size_t			id;
	t_table			*table;
	struct timeval	lastmeal;
}	t_philo;

int		p_eat(t_philo *me);
int		p_sleep(t_philo *me);
int		p_think(t_philo *me);
void	*lifeofaphilo(void *p);

long	usecsince(struct timeval ref);
int		deadcheck(t_philo *me);
int		p_status(t_philo *me, char *s);
long	min(long a, long b);

int		readinput(int argc, const char *argv[],
			t_philo **philos, t_table **table);

#endif
