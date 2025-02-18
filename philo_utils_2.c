/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:27:29 by ylabussi          #+#    #+#             */
/*   Updated: 2025/02/18 17:22:02 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_think(t_philo *me)
{
	t_table	*table;

	table = me->table;
	if (deadcheck(me))
		return (1);
	printf("%6li %3li is thinking\n",
		usecsince(table->start) / 1000, me->id);
	if (mutex_lock_timed(&(table->forks[me->id - 1]), me))
		return (1);
	printf("%6li %3li has taken a fork\n",
		usecsince(table->start) / 1000, me->id);
	if (mutex_lock_timed(&(table->forks[me->id % table->n_philo]), me))
	{
		pthread_mutex_unlock(&(table->forks[me->id - 1]));
		return (1);
	}
	printf("%6li %3li has taken a fork\n",
		usecsince(table->start) / 1000, me->id);
	return (0);
}

void	p_lock_start(t_philo *me)
{
	p_think(me);
}

int	p_eat(t_philo *me)
{
	t_table	*table;
	int		status;

	table = me->table;
	status = deadcheck(me);
	if (!status)
	{
		printf("%6li %3li is eating\n",
			usecsince(table->start) / 1000, me->id);
		gettimeofday(&me->lastmeal, NULL);
		usleep(table->tte);
	}
	pthread_mutex_unlock(&(table->forks[me->id - 1]));
	pthread_mutex_unlock(&(table->forks[me->id % table->n_philo]));
	return (status);
}

int	p_sleep(t_philo *me)
{
	t_table	*table;

	table = me->table;
	if (!deadcheck(me))
	{
		printf("%6li %3li is sleeping\n",
			usecsince(table->start) / 1000, me->id);
		usleep(table->tts);
		return (0);
	}
	return (1);
}

void	*lifeofaphilo(void *p)
{
	t_philo	*me;
	int		i;

	me = p;
	i = 0;
	gettimeofday(&me->lastmeal, NULL);
	if (me->table->n_philo == 1)
	{
		usleep(me->table->ttd);
		deadcheck(me);
		return (NULL);
	}
	p_lock_start(me);
	while (i != me->table->max_meals)
	{
		if (p_eat(me) || p_sleep(me))
			break ;
		if (me->table->max_meals > 0)
			i++;
		if (i != me->table->max_meals && p_think(me))
			break ;
	}
	return (NULL);
}
