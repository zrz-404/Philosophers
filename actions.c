/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:50:00 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/17 21:15:02 by jroseiro         ###   ########.fr       */
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
	if (philo->phi_num == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
		ft_usleep(1);
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		ft_usleep(1);
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
	}
}

void	release_forks(t_phi *philo)
{
	if (philo->phi_num == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
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
	if (check_dead_flag(philo))
	{
		release_forks(philo);
		return ;
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	print_status(philo, "is eating");
	ft_usleep(philo->t_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	release_forks(philo);
}

// philo->phi_num == 1 ||