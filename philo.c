/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:21:57 by ylabussi          #+#    #+#             */
/*   Updated: 2025/02/17 16:10:36 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_start(t_philo *philos, t_table *table)
{
	size_t	i;

	i = 0;
	gettimeofday(&(table->start), NULL);
	while (i < table->nphilos)
	{
		philos[i].id = i + 1;
		philos[i].table = table;
		pthread_create(&(philos[i].tid), NULL, &lifeofaphilo, &(philos[i]));
		i++;
	}
	while (i > 0)
		pthread_join(philos[--i].tid, NULL);
	if (table->deadphilo)
		printf("%6li %3li died \n",
			usecsince(table->start) / 1000, table->deadphilo);
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
		return (1);
	e = 0;
	i = 0;
	status = 1;
	while (i < table->nphilos)
		e |= pthread_mutex_init(&(table->forks[i++]), NULL);
	if (!e)
		status = philo_start(philos, table);
	while (i > 0)
		pthread_mutex_destroy(&(table->forks[--i]));
	free(philos);
	free(table->forks);
	free(table);
	return (status);
}
