/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:14:46 by ple-guya          #+#    #+#             */
/*   Updated: 2024/10/30 23:06:48 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ph_atos(char *s)
{
	size_t	resultat;
	int		i;

	i = 0;
	resultat = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			return (0);
		i++;
	}
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		resultat = resultat * 10 + (s[i] - 48);
		i++;
	}
	return (resultat);
}

void	print_philo(t_data *data, size_t id, char *msg)
{
	size_t	now;

	now = get_time();
	pthread_mutex_lock(&data->monitor);
	if (!dead(data))
		printf("%zu %zu %s", now - data->start_time, id, msg);
	pthread_mutex_unlock(&data->monitor);
}

size_t	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (0);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	dead(t_data *data)
{
	int	stop;

	stop = 0;
	pthread_mutex_lock(&data->dead_lock);
	stop = data->is_dead;
	pthread_mutex_unlock(&data->dead_lock);
	return (stop);
}

void	wait_philo(t_data *data, size_t wait_time)
{
	size_t	start;
	size_t	now;

	start = get_time();
	now = start;
	while (now - start <= wait_time)
	{
		if (dead(data))
			return ;
		usleep(100);
		now = get_time();
	}
}
