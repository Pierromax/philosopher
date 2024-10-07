/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:16:54 by ple-guya          #+#    #+#             */
/*   Updated: 2024/10/03 21:14:00 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (ft_putstr_fd("philo malloc failed\n", 2), 1);
	if (ac < 5 || ac > 6)
		return (printf(BAD_ARG_NBR), 1);
	if (init_philo(&philo, av))
		return (1);
	if (create_mutex(philo))
		return (printf("failed creating mutex"));
	if (create_threads(philo))
		return (printf("failed creating threads"));
	return (0);
}
