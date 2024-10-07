/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:34:33 by ple-guya          #+#    #+#             */
/*   Updated: 2024/10/03 21:12:56 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_mutex(t_philo *ph, t_data *data)
{
	size_t	i;

	i = 0;
	if (pthread_mutex_init(&(ph->eat_lock), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(ph->dead_lock), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(ph->sleep_lock), NULL) != 0)
		return (1);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init((&(ph->fork[i])), NULL) != 0)
		{
			while (i-- > 0)
				free(ph[i].fork);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	create_threads(t_philo *ph)
{
	size_t	i;
	t_data	*data;

	data = ph->data;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&ph[i].philo, NULL, routine, &ph[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(ph[i].philo, NULL))
			return (1);
		i++;
	}
	return (0);
}

t_data	*init_data(char **av)
{
	t_data	*data;
	int		i;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	i = 1;
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_must_eat = ft_atoi(av[5]);
	return (data);
}

int	init_philo(t_philo **philo, char **av)
{
	t_data	*data;
	size_t	i;

	i = 0;
	data = init_data(av);
	if (!data)
		return (1);
	*philo = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (1);
	(*philo)->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->nb_philo);
	while (i < data->nb_philo)
	{
		(*philo)[i].data = data;
		(*philo)[i].id = i;
		i++;
	}
	return (0);
}
