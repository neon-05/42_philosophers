/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:29:12 by ylabussi          #+#    #+#             */
/*   Updated: 2025/03/07 16:46:05 by ylabussi         ###   ########.fr       */
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
	else if (usecsince(me->lastmeal) > table->ttd)
	{
		table->deadphilo = me->id;
		printf("%6li %3li died\n",
			usecsince(me->table->start) / 1000, me->id);
		return (1);
	}
	else
		return (0);
}

int	p_status(t_philo *me, char *s)
{
	int	r;

	pthread_mutex_lock(&me->table->deadphilo_lock);
	r = deadcheck(me);
	if (!r)
		printf("%6li %3li %s\n",
			usecsince(me->table->start) / 1000, me->id, s);
	pthread_mutex_unlock(&me->table->deadphilo_lock);
	return (r);
}

long	min(long a, long b)
{
	if (a > b)
		return (b);
	else
		return (a);
}
