/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:34:33 by ple-guya          #+#    #+#             */
/*   Updated: 2024/10/30 23:06:30 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_mutex(t_data *data)
{
	size_t	i;

	i = 0;
	if (pthread_mutex_init(&(data->monitor), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(data->dead_lock), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(data->eat_lock), NULL) != 0)
		return (1);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init((&(data->fork[i])), NULL) != 0)
		{
			while (i-- > 0)
				free(data[i].fork);
			return (1);
		}
		i++;
	}
	return (0);
}

t_data	*init_data(char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->is_dead = 0;
	data->nb_must_eat = 0;
	data->is_full = 0;
	data->nb_philo = ph_atos(av[1]);
	data->time_to_die = ph_atos(av[2]);
	data->time_to_eat = ph_atos(av[3]);
	data->time_to_sleep = ph_atos(av[4]);
	if (data->nb_philo == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0)
		return (printf("enter valid argument\n"), NULL);
	if (av[5])
	{
		data->nb_must_eat = ph_atos(av[5]);
		if (!data->nb_must_eat)
			return (printf("enter valid argument\n"), NULL);
	}
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (printf("failed creating forks mutex"), NULL);
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
	if (!(*philo))
		return (1);
	data->start_time = get_time();
	while (i < data->nb_philo)
	{
		(*philo)[i].last_meal = get_time();
		(*philo)[i].has_eaten = 0;
		(*philo)[i].data = data;
		(*philo)[i].id = i + 1;
		(*philo)[i].r_fork = i;
		(*philo)[i].l_fork = (i + 1) % data->nb_philo;
		i++;
	}
	if (create_mutex(data))
		return (printf("failed creating mutex"));
	return (0);
}
