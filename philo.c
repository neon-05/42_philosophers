/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:21:57 by ylabussi          #+#    #+#             */
/*   Updated: 2025/01/30 18:55:10 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_eat(t_philo *me);
int	p_sleep(t_philo *me);
int	p_think(t_philo *me);

int	p_eat(t_philo *me)
{
	t_table	*table;

	table = me->table;
	if (deadcheck(me))
		return (1);
	if (mutex_lock_timed(&(table->forks[me->id]), me)
		|| mutex_lock_timed(&(table->forks[me->id + 1 % table->nphilos]), me))
		return (1);
	if (!deadcheck(me))
	{
		printf("%6li %3li is eating\n", usecsince(table->start) / 1000, me->id);
		gettimeofday(&me->lastmeal, NULL);
		usleep(min(table->tte, table->ttd));
	}
	pthread_mutex_unlock(&(table->forks[me->id]));
	pthread_mutex_unlock(&(table->forks[me->id + 1 % table->nphilos]));
	return (0);
}

int	p_sleep(t_philo *me)
{
	t_table	*table;

	table = me->table;
	if (!deadcheck(me))
	{
		printf("%6li %3li is sleeping\n", usecsince(table->start) / 1000, me->id);
		usleep(min(table->tts, table->ttd - table->tte));
		return (0);
	}
	return (1);
}

int	p_think(t_philo *me)
{
	t_table	*table;

	table = me->table;
	if (!deadcheck(me))
	{
		printf("%6li %3li is thinking\n", usecsince(table->start) / 1000, me->id);
		return (0);
	}
	return (1);
}

void	*philo(void *p)
{
	t_philo			*me;

	me = p;
	gettimeofday(&me->lastmeal, NULL);
	while (me->max_meals)
	{
		if (p_eat(me) || p_sleep(me) || p_think(me) || deadcheck(me))
			break ;
		me->max_meals -= (me->max_meals > 0);
	}
	return (NULL);
}

int	main(void)
{
	size_t	i;
	t_philo	*philos;
	t_table	*table;

	table = malloc(sizeof(t_table));
	table->nphilos = 5;
	table->ttd = 450 * 1000;
	table->tte = 200 * 1000;
	table->tts = 200 * 1000;
	table->deadphilo = 0;
	philos = malloc(sizeof(t_philo) * (table->nphilos+1));
	table->forks = malloc(sizeof(pthread_mutex_t) * (table->nphilos+1));
	i = 0;
	while (i < table->nphilos)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		i++;
	}
	gettimeofday(&(table->start), NULL);
	i = 0;
	while (i < table->nphilos)
	{
		philos[i].id = i;
		philos[i].table = table;
		philos[i].max_meals = 20;
		pthread_create(&(philos[i].tid), NULL, &philo, &(philos[i]));
		i++;
	}
	i = 0;
	while (i < table->nphilos)
	{
		pthread_join(philos[i].tid, NULL);
		i++;
	}
	if (table->deadphilo)
		printf("%6li %3li died \n", usecsince(table->start) / 1000, table->deadphilo-1);
	free(philos);
	free(table->forks);
	free(table);
	return (0);
}
