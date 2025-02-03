/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:22:30 by ylabussi          #+#    #+#             */
/*   Updated: 2025/02/03 15:18:10 by ylabussi         ###   ########.fr       */
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

typedef struct s_table
{
	size_t			nphilos;
	pthread_mutex_t	*forks;
	long			ttd;
	long			tte;
	long			tts;
	int				max_meals;
	size_t			deadphilo;
	struct timeval	start;
}	t_table;

typedef struct s_philo
{
	pthread_t		tid;
	size_t			id;
	t_table			*table;
	struct timeval	lastmeal;
}	t_philo;

long	usecsince(struct timeval ref);
int		deadcheck(t_philo *me);
int		mutex_lock_timed(pthread_mutex_t *mutex, t_philo *me);
long	min(long a, long b);
int		max(int a, int b);

int		readinput(int argc, const char *argv[],
			t_philo **philos, t_table **table);
int		alloc(t_philo **philos, t_table **table, size_t n);
int		ft_atoi(const char *s);

int		p_eat(t_philo *me);
int		p_sleep(t_philo *me);
int		p_think(t_philo *me);
void	*lifeofaphilo(void *p);

#endif
