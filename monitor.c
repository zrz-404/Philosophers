/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:52:04 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/17 21:17:08 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sources.h"

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

int	check_philosopher_death(t_phi *philo)
{
	size_t	time;
	size_t	last_meal_time;

	pthread_mutex_lock(philo->meal_lock);
	if (philo->eating == 1)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (0);
	}
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(philo->meal_lock);
	time = get_current_time();
	if (time - last_meal_time >= philo->t_die)
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		print_status(philo, "died");
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	return (0);
}

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
	ft_usleep(5);
	while (1)
	{
		i = 0;
		while (i < philos[0].phi_num)
		{
			if (check_philosopher_death(&philos[i]) == 1)
				return (NULL);
			if (i % 10 == 0)
				ft_usleep(1);
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
}
