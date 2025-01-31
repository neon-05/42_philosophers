/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:27:29 by ylabussi          #+#    #+#             */
/*   Updated: 2025/01/31 16:53:52 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_eat(t_philo *me)
{
	t_table	*table;

	table = me->table;
	if (deadcheck(me))
		return (1);
	if (mutex_lock_timed(&(table->forks[me->id]), me))
		return (1);
	pthread_mutex_lock(&(table->forks[(me->id + 1) % table->nphilos]));
	if (!deadcheck(me))
	{
		printf("%6li %3li is eating\n",
			usecsince(table->start) / 1000, me->id);
		gettimeofday(&me->lastmeal, NULL);
		usleep(min(table->tte, table->ttd));
	}
	pthread_mutex_unlock(&(table->forks[me->id]));
	pthread_mutex_unlock(&(table->forks[(me->id + 1) % table->nphilos]));
	return (deadcheck(me));
}

int	p_sleep(t_philo *me)
{
	t_table	*table;

	table = me->table;
	if (!deadcheck(me))
	{
		printf("%6li %3li is sleeping\n",
			usecsince(table->start) / 1000, me->id);
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
		printf("%6li %3li is thinking\n",
			usecsince(table->start) / 1000, me->id);
		return (0);
	}
	return (1);
}

void	*philo(void *p)
{
	t_philo	*me;
	int		i;

	me = p;
	i = 0;
	gettimeofday(&me->lastmeal, NULL);
	while (i < me->table->max_meals)
	{
		if (p_eat(me) || p_sleep(me) || p_think(me) || deadcheck(me))
			break ;
		i += (me->table->max_meals > 0);
	}
	return (NULL);
}
