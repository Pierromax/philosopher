/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:18:07 by ple-guya          #+#    #+#             */
/*   Updated: 2024/10/30 23:40:28 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_full(t_data *data)
{
	pthread_mutex_lock(&data->eat_lock);
	if ((data->nb_must_eat != 0) && data->is_full >= data->nb_philo)
	{
		pthread_mutex_unlock(&data->eat_lock);
		printf("Everyone eat enough\n");
		return (1);
	}
	pthread_mutex_unlock(&data->eat_lock);
	return (0);
}

void	dead_check(t_data *data, t_philo *ph)
{
	size_t	i;
	size_t	now;
	size_t	last_meal_cp;

	while (!dead(data) && !is_full(data))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			now = get_time();
			pthread_mutex_lock(&data->eat_lock);
			last_meal_cp = ph[i].last_meal;
			pthread_mutex_unlock(&data->eat_lock);
			if ((now - last_meal_cp >= data->time_to_die))
			{
				print_philo(data, i, DEAD);
				pthread_mutex_lock(&data->dead_lock);
				data->is_dead = 1;
				pthread_mutex_unlock(&data->dead_lock);
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}

static void	*aucun_ami_a_la_cantine(t_philo *ph)
{
	t_data	*data;

	data = ph->data;
	pthread_mutex_lock(&data->fork[0]);
	print_philo(data, ph->id, FORK);
	pthread_mutex_unlock(&data->fork[0]);
	wait_philo(data, data->time_to_die);
	data->is_dead = 1;
	return (NULL);
}

static void	eat_routine(t_data *data, t_philo *ph)
{
	int	first_fork;
	int	second_fork;

	first_fork = (ph->id + (ph->id % 2 == 1)) % ph->data->nb_philo;
	second_fork = (ph->id + (ph->id % 2 == 0)) % ph->data->nb_philo;
	pthread_mutex_lock(&data->fork[first_fork]);
	print_philo(data, ph->id, FORK);
	pthread_mutex_lock(&data->fork[second_fork]);
	print_philo(data, ph->id, FORK);
	print_philo(data, ph->id, EAT);
	wait_philo(data, data->time_to_eat);
	pthread_mutex_lock(&data->eat_lock);
	ph->last_meal = get_time();
	pthread_mutex_unlock(&(data->eat_lock));
	pthread_mutex_lock(&data->eat_lock);
	ph->has_eaten++;
	pthread_mutex_unlock(&(data->eat_lock));
	pthread_mutex_unlock(&data->fork[second_fork]);
	pthread_mutex_unlock(&data->fork[first_fork]);
}

void	*philo_routine(void *param)
{
	t_philo	*ph;
	t_data	*data;

	ph = (t_philo *)param;
	data = ph->data;
	ph->last_meal = get_time();
	if (data->nb_philo == 1)
		return (aucun_ami_a_la_cantine(ph));
	if (ph->id % 2 == 0)
		usleep(1000);
	while (!dead(data))
	{
		eat_routine(data, ph);
		if (ph->has_eaten == data->nb_must_eat)
		{	
			pthread_mutex_lock(&data->eat_lock);
			data->is_full++;
			pthread_mutex_unlock(&data->eat_lock);
			break ;
		}
		print_philo(data, ph->id, SLEEP);
		wait_philo(data, data->time_to_sleep);
		print_philo(data, ph->id, THINK);
	}
	return (NULL);
}
