/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:57:59 by ylabussi          #+#    #+#             */
/*   Updated: 2025/02/03 15:03:28 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *s)
{
	int		n;
	int		sign;
	size_t	i;

	i = 0;
	n = 0;
	sign = 1;
	while (s[i] == ' ' || ('\t' <= s[i] && s[i] <= '\r'))
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	while ('0' <= s[i] && s[i] <= '9')
	{
		n = n * 10 + s[i] - '0';
		i++;
	}
	return (sign * n);
}

int	alloc(t_philo **philos, t_table **table, size_t n)
{
	*table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	(*table)->forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!(*table)->forks)
	{
		free(*table);
		return (1);
	}
	*philos = malloc(sizeof(t_philo) * n);
	if (!(*philos))
	{
		free((*table)->forks);
		free(*table);
		return (1);
	}
	return (0);
}

int	readinput(int argc, const char *argv[], t_philo **philos, t_table **table)
{
	size_t	n_philo;

	if (argc < 5 || argc > 6)
	{
		printf("usage: %s <nb_philo> <ttd> <tte> <tts> [nb_meals]\n", argv[0]);
		return (1);
	}
	n_philo = ft_atoi(argv[1]);
	if (alloc(philos, table, n_philo))
		return (1);
	(*table)->nphilos = n_philo;
	(*table)->deadphilo = 0;
	(*table)->ttd = max(0, ft_atoi(argv[2])) * 1000;
	(*table)->tte = max(0, ft_atoi(argv[3])) * 1000;
	(*table)->tts = max(0, ft_atoi(argv[4])) * 1000;
	(*table)->max_meals = -1;
	if (argc == 6)
		(*table)->max_meals = max(-1, ft_atoi(argv[5]));
	return (0);
}
