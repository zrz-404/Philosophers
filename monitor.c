/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:52:04 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/16 01:40:57 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sources.h"

// a function to print the required messages

int	check_if_dead(t_phi *philo)
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

// A function to check if a philosopher is dead

int	check_philosopher_death(t_phi *philo)
{
	size_t	time;

	if (philo->eating == 1)
		return (0);
	time = get_current_time();
	if (time - philo->last_meal >= philo->t_die)
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		print_status(philo, "died");
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	return (0);
}

// Check if all the philosophers ate the number of meals assigned in the input

int	check_all_ate(t_phi *philos)
{
	int	i;
	int	done_eating;

	i = 0;
	done_eating = 0;
	if (philos[0].n_eat == -1)
		return (0);
	while (i < philos[0].phi_num)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].n_eat)
			done_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (done_eating == philos[0].phi_num)
		return (1);
	return (0);
}

void	*monitor_routine(void *pointer)
{
	t_phi	*philos;
	int		i;

	philos = (t_phi *)pointer;
	while (1)
	{
		i = 0;
		while (i < philos[0].phi_num)
		{
			if (check_philosopher_death(&philos[i]) == 1)
				return (NULL);
			i++;
		}
		if (check_all_ate(philos) == 1)
		{
			pthread_mutex_lock(philos[0].dead_lock);
			*philos[0].dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (NULL);
		}
		ft_usleep(1);
	}
	return (NULL);
}

