/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:27:58 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/16 01:15:42 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sources.h"

// A function to heck if the value of dead_flag changed
int	check_dead_flag(t_phi *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

// Thread routine
void	*philo_routine(void *pointer)
{
	t_phi *philo;

	philo = (t_phi *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (check_dead_flag(philo) != 1)
	{
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

// Creating all the threads
int	create_threads(t_phi *philos, t_exe *exe)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (1 < philos[0].phi_num)
	{
		philos[i].dead = &exe->f_dead;
		if (pthread_create(&philos[i].thread, NULL,
			&philo_routine, &philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitor_routine, philos) != 0)
		return (1);
	i = 0;
	while (i < philos[0].phi_num)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	return (0);
}
