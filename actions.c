/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:50:00 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/16 18:07:20 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// a function for the thinking action, also prints that it is perfomring this action

// a function for the sleeping action, also prints that it is performing this action

// a function for the eating action which, not only prints that it is performing this action, but also before prints when a fork is taken

#include "sources.h"

void	print_status(t_phi *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

void	think(t_phi *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead != 1)
		print_status(philo, "is thinking");
	pthread_mutex_unlock(philo->dead_lock);
}

void	sleeping(t_phi *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead != 1)
	{
		print_status(philo, "is sleeping");
		pthread_mutex_unlock(philo->dead_lock);
		ft_usleep(philo->t_sleep);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
}

void	take_forks(t_phi *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead != 1)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead != 1)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(philo->dead_lock);
}

void	release_forks(t_phi *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	update_meal_count(t_phi *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
}

void	eat(t_phi *philo)
{
	take_forks(philo);
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead != 1)
	{
		print_status(philo, "is eating");
		pthread_mutex_lock(philo->meal_lock);
		philo->eating = 1;
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(philo->meal_lock);
		pthread_mutex_unlock(philo->dead_lock);
		ft_usleep(philo->t_eat);
		update_meal_count(philo);
		pthread_mutex_lock(philo->meal_lock);
		philo->eating = 0;
		release_forks(philo);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	release_forks(philo);
}

