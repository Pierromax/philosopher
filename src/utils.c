/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:14:46 by ple-guya          #+#    #+#             */
/*   Updated: 2024/10/03 21:36:55 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_atos(char *s)
{
	size_t	resultat;
	int		i;

	i = 0;
	resultat = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] && ft_isdigit(s[i]))
		resultat = resultat * 10 + (s[i++] - 48);
	if (resultat == 0 || !ft_isdigit(s[i]))
		return (printf("enter a valid number\n"), 0);
	else
		return (resultat);
}

size_t	get_time()
{
	struct timeval	*current_time;
	int				start_time;

	start_time = gettimeofday(current_time, NULL);
	printf("current_time = %d\n", start_time);
	
}
