/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:13:31 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/19 17:31:40 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sources.h"

void	print_status(t_phi *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	printf("%zums  philo %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

void	update_meal_count(t_phi *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
}

void	take_one_fork(t_phi *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	if (!check_dead_flag(philo))
		print_status(philo, "has taken a fork");
}

void	take_forks_even(t_phi *philo)
{
	take_one_fork(philo, philo->r_fork);
	if (check_dead_flag(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	take_one_fork(philo, philo->l_fork);
	if (check_dead_flag(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
}

void	take_forks_odd(t_phi *philo)
{
	take_one_fork(philo, philo->l_fork);
	if (check_dead_flag(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	take_one_fork(philo, philo->r_fork);
	if (check_dead_flag(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
}
