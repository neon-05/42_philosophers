/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:52:23 by ylabussi          #+#    #+#             */
/*   Updated: 2025/03/10 16:10:08 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_eat(t_philo *me)
{
	t_table	*table;

	table = me->table;
	pthread_mutex_lock(&table->forks[me->id - 1 % table->n_philo]);
	if (p_status(me, "has taken a fork"))
	{
		pthread_mutex_unlock(&table->forks[me->id - 1 % table->n_philo]);
		return (1);
	}
	pthread_mutex_lock(&table->forks[me->id % table->n_philo]);
	if (p_status(me, "has taken a fork"))
	{
		pthread_mutex_unlock(&table->forks[me->id - 1 % table->n_philo]);
		pthread_mutex_unlock(&table->forks[me->id % table->n_philo]);
		return (1);
	}
	p_status(me, "is eating");
	gettimeofday(&me->lastmeal, NULL);
	usleep(min(table->tte, table->ttd));
	pthread_mutex_unlock(&table->forks[me->id - 1 % table->n_philo]);
	pthread_mutex_unlock(&table->forks[me->id % table->n_philo]);
	return (0);
}

int	p_sleep(t_philo *me)
{
	t_table	*table;

	table = me->table;
	if (p_status(me, "is sleeping"))
		return (1);
	usleep(min(table->tts, table->ttd - table->tte));
	return (0);
}

int	p_think(t_philo *me)
{
	t_table	*table;

	table = me->table;
	if (p_status(me, "is thinking"))
		return (1);
	if (table->ttd > table->tte * 2)
	{
		if (table->tte > table->tts)
			usleep(table->tte - table->tts);
	}
	else
		usleep(table->ttd - table->tte - table->tts);
	return (0);
}

int	p_lonely_philo(t_philo *me)
{
	usleep(me->table->ttd);
	return (deadcheck(me));
}

void	*lifeofaphilo(void *p)
{
	t_philo	*me;
	t_table	*table;
	int		i;

	i = 0;
	me = p;
	table = me->table;
	if (table->n_philo == 1)
	{
		p_lonely_philo(me);
		return (NULL);
	}
	if (!(me->id & 1))
		usleep(500);
	me->lastmeal = table->start;
	while (i != table->max_meals)
	{
		if (p_eat(me) || p_sleep(me) || p_think(me) || deadcheck(me))
			break ;
		if (table->max_meals > 0)
			i++;
	}
	return (NULL);
}
