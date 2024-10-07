/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:33:26 by ple-guya          #+#    #+#             */
/*   Updated: 2024/10/03 21:43:02 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define BAD_ARG_NBR "error syntax : \n\
./philo [ philo_nbr ] [ time_to_die ] [ time_to_eat ] \
[ time_to_sleep ] [ number_of_meal_each_philo_must_have ]\n\
optionnal argument : number_of_meal_each_philo_must_have "

typedef	struct	s_data
{
	size_t		nb_philo;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		nb_must_eat;
}	t_data;

typedef	struct s_philo
{
	pthread_t		philo;
	size_t			id;
	int				is_dead;
	int				r_fork;
	int 			l_fork;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	sleep_lock;
	pthread_mutex_t	*fork;
	t_data			*data;
}	t_philo;

// init struct
t_data	*init_data(char **arg);
int		init_philo(t_philo **philo, char **arg);
// Thread Routine
void	*routine(void *param);

# endif