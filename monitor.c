/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:52:04 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/19 17:29:28 by jroseiro         ###   ########.fr       */
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
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(philo->meal_lock);
	time = get_current_time();
	if ((time - last_meal_time) >= philo->t_die)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*philo->dead != 1)
		{
			*philo->dead = 1;
			print_status(philo, "died");
		}
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	return (0);
}

int	check_all_ate(t_phi *philos)
{
	int	i;
	int	total_meals;

	i = 0;
	total_meals = 0;
	if (philos[0].n_eat == -1)
		return (0);
	if (philos[0].n_eat == 0)
		return (1);
	pthread_mutex_lock(philos[0].meal_lock);
	while (i < philos[0].phi_num)
	{
		total_meals += philos[i].meals_eaten;
		i++;
	}
	pthread_mutex_unlock(philos[0].meal_lock);
	if (total_meals >= (philos[0].phi_num * philos[0].n_eat))
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos[0].dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

// static void	set_dead_flag(t_phi *philos)
// {
// 	pthread_mutex_lock(philos[0].dead_lock);
// 	*philos[0].dead = 1;
// 	pthread_mutex_unlock(philos[0].dead_lock);
// }

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
		if (check_all_ate(philos))
		{
			pthread_mutex_lock(philos[0].dead_lock);
			*philos[0].dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (NULL);
		}
		usleep(10);
	}
}
