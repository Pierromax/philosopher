/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:33:26 by ple-guya          #+#    #+#             */
/*   Updated: 2024/10/30 23:41:35 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define BAD_ARG_NBR "error syntax : \n\
./philo [ nb_philo ] [ time_to_die ] [ time_to_eat ] \
[ time_to_sleep ] [ number_of_meal_each_philo_must_have ]*\n\
*number_of_meal_each_philo_must_have is an optionnal argument "
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define PRP "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define DEAD "\e[0;31mdied\e[0;37m\n"
# define FORK "\e[0;34mhas taken a fork\e[0;37m\n"
# define EAT "\e[0;35mis eating\e[0;37m\n"
# define SLEEP "\e[0;36mis sleeping\e[0;37m\n"
# define THINK "\e[0;32mis thinking\e[0;37m\n"

typedef struct s_data
{
	size_t			nb_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			nb_must_eat;
	size_t			start_time;
	size_t			is_full;
	int				is_dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	monitor;
	pthread_mutex_t	*fork;
}	t_data;

typedef struct s_philo
{
	pthread_t		philo;
	size_t			id;
	size_t			last_meal;
	size_t			has_eaten;
	int				r_fork;
	int				l_fork;
	t_data			*data;
}	t_philo;

// init struct
t_data	*init_data(char **arg);
int		init_philo(t_philo **philo, char **arg);
int		create_mutex(t_data *data);

// Thread Routine
void	*philo_routine(void *param);
int		start_simulation(t_philo *philo);

//utils
void	wait_philo(t_data *data, size_t wait_time);
size_t	ph_atos(char *nbptr);
int		free_all(t_philo *philo);
size_t	get_time(void);
int		dead(t_data *data);

//monitor
void	print_philo(t_data *data, size_t id, char *msg);
void	dead_check(t_data *data, t_philo *ph);

#endif