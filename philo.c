/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:51:27 by ylabussi          #+#    #+#             */
/*   Updated: 2025/03/07 16:28:55 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_loop(t_philo *philos, t_table *table, size_t offset)
{
	size_t	i;

	i = offset;
	while (i < table->n_philo)
	{
		philos[i].id = i + 1;
		philos[i].table = table;
		if (pthread_create(&(philos[i].tid), NULL, &lifeofaphilo, &(philos[i])))
		{
			table->deadphilo = i + 1;
			return (1);
		}
		i += 2;
	}
	return (0);
}

int	philo_start(t_philo *philos, t_table *table)
{
	size_t	i;

	i = 0;
	gettimeofday(&(table->start), NULL);
	if (start_loop(philos, table, 0))
		return (3);
	usleep(50);
	if (start_loop(philos, table, 1))
		return (3);
	while (i < table->n_philo)
		pthread_join(philos[i++].tid, NULL);
	return (table->deadphilo != 0);
}

int	main(int argc, const char *argv[])
{
	size_t	i;
	int		e;
	int		status;
	t_philo	*philos;
	t_table	*table;

	if (readinput(argc, argv, &philos, &table))
		return (2);
	e = 0;
	i = 0;
	status = 1;
	while (i < table->n_philo)
		e |= pthread_mutex_init(&(table->forks[i++]), NULL);
	e |= pthread_mutex_init(&table->deadphilo_lock, NULL);
	if (!e)
		status = philo_start(philos, table);
	while (i > 0)
		pthread_mutex_destroy(&(table->forks[--i]));
	pthread_mutex_destroy(&table->deadphilo_lock);
	free(philos);
	free(table->forks);
	free(table);
	return (status);
}
