/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:27:29 by ylabussi          #+#    #+#             */
/*   Updated: 2025/02/03 16:53:30 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		usleep(min(table->tte, table->ttd));
	}
	pthread_mutex_unlock(&(table->forks[me->id]));
	pthread_mutex_unlock(&(table->forks[(me->id + 1) % table->nphilos]));
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
		usleep(min(table->tts, table->ttd - table->tte));
		return (0);
	}
	return (1);
}

int	p_think(t_philo *me)
{
	t_table	*table;

	table = me->table;
	if (deadcheck(me))
		return (1);
	printf("%6li %3li is thinking\n",
		usecsince(table->start) / 1000, me->id);
	if (mutex_lock_timed(&(table->forks[me->id]), me))
		return (1);
	if (mutex_lock_timed(&(table->forks[(me->id + 1) % table->nphilos]), me))
	{
		pthread_mutex_unlock(&(table->forks[me->id]));
		return (1);
	}
	return (0);
}

void	*lifeofaphilo(void *p)
{
	t_philo	*me;
	int		i;

	me = p;
	i = 0;
	gettimeofday(&me->lastmeal, NULL);

	if (me->table->nphilos == 1)
	{
		usleep(me->table->ttd);
		deadcheck(me);
		return (NULL);
	}
	while (i != me->table->max_meals)
	{
		if (p_think(me) || p_eat(me) || p_sleep(me))
			break ;
		if (me->table->max_meals > 0)
			i++;
	}
	return (NULL);
}
