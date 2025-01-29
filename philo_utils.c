/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:29:12 by ylabussi          #+#    #+#             */
/*   Updated: 2025/01/29 18:30:04 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	usecsince(struct timeval ref)
{
	struct timeval	now;
	long			sec;
	long			usec;

	if (gettimeofday(&now, NULL))
		return (0);
	sec = now.tv_sec - ref.tv_sec;
	usec = now.tv_usec - ref.tv_usec;
	return (sec * 1000000 + usec);
}

int	deadcheck(t_philo *me)
{
	t_table	*table;

	table = me->table;
	if (table->deadphilo)
		return (1);
	if (usecsince(me->lastmeal) > table->ttd)
	{
		printf("%5li %3li is dead \n", usecsince(table->start) / 1000, me->id);
		table->deadphilo = me->tid;
		return (1);
	}
	else
		return (0);
}

int	mutex_lock_timed(pthread_mutex_t *mutex, t_philo *me)
{
	pthread_mutex_lock(mutex);
	if (deadcheck(me))
	{
		pthread_mutex_unlock(mutex);
		return (1);
	}
	else
		return (0);
}
