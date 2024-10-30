/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:16:54 by ple-guya          #+#    #+#             */
/*   Updated: 2024/10/30 23:41:10 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_all(t_philo *philo)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = philo->data->nb_philo;
	pthread_mutex_destroy(&philo->data->monitor);
	pthread_mutex_destroy(&philo->data->dead_lock);
	pthread_mutex_destroy(&philo->data->eat_lock);
	while (i < size)
		pthread_mutex_destroy(&philo->data->fork[i++]);
	free(philo->data->fork);
	free(philo->data);
	free(philo);
	return (1);
}

int	start_simulation(t_philo *ph)
{
	size_t	i;

	i = 0;
	while (i < ph->data->nb_philo)
	{
		ph[i].last_meal = get_time();
		if (pthread_create(&ph[i].philo, NULL, philo_routine, &ph[i]))
			return (printf("pthread creation failed"));
		i++;
	}
	dead_check(ph->data, ph);
	i = 0;
	while (i < ph->data->nb_philo)
	{
		if (pthread_join(ph[i].philo, NULL))
			return (printf("pthread joining failed"));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (printf(BAD_ARG_NBR), 1);
	if (init_philo(&philo, av))
		return (1);
	if (start_simulation(philo))
		return (1);
	free_all(philo);
	return (0);
}
