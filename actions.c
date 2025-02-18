/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:50:00 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/18 20:17:11 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sources.h"

void	think(t_phi *philo)
{
	size_t	think_time;

	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead != 1)
	{
		print_status(philo, "is thinking");
		pthread_mutex_unlock(philo->dead_lock);
		think_time = (philo->t_die - (philo->t_eat + philo->t_sleep)) / 2;
		if (think_time > 0)
			ft_usleep(think_time);
		return ;
	}
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
	if (check_dead_flag(philo))
		return ;
	if (philo->phi_num == 1)
	{
		take_one_fork(philo, philo->l_fork);
		return ;
	}
	if (philo->id % 2 == 0)
		take_forks_even(philo);
	else
		take_forks_odd(philo);
}

void	release_forks(t_phi *philo)
{
	if (philo->phi_num == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	eat(t_phi *philo)
{
	take_forks(philo);
	if (check_dead_flag(philo))
	{
		release_forks(philo);
		return ;
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_current_time();
	print_status(philo, "is eating");
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->t_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	release_forks(philo);
}

// philo->phi_num == 1 ||