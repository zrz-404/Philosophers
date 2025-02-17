/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:50:00 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/17 17:43:53 by jroseiro         ###   ########.fr       */
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
	printf("%zums  philo %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->write_lock);
}


// void    think(t_phi *philo) -- last working version
// {
//     size_t time_to_think;

//     pthread_mutex_lock(philo->dead_lock);
//     if (*philo->dead != 1)
//     {
//         print_status(philo, "is thinking");
//         // Calculate thinking time to prevent starvation
//         time_to_think = (philo->t_die - (philo->t_eat + philo->t_sleep)) / 2;
//         pthread_mutex_unlock(philo->dead_lock);
//         if (time_to_think > 0)
//             ft_usleep(time_to_think);
//         return;
//     }
//     pthread_mutex_unlock(philo->dead_lock);
// }


void    think(t_phi *philo)
{
	size_t think_time;

	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead != 1)
	{
		print_status(philo, "is thinking");
		pthread_mutex_unlock(philo->dead_lock);
		// Calculate optimal thinking time
		think_time = (philo->t_die - (philo->t_eat + philo->t_sleep)) / 2;
		if (think_time > 0)
			ft_usleep(think_time);
		return;
	}
	pthread_mutex_unlock(philo->dead_lock);
}


void    sleeping(t_phi *philo)

{

	pthread_mutex_lock(philo->dead_lock);

	if (*philo->dead != 1)

	{

		print_status(philo, "is sleeping");

		pthread_mutex_unlock(philo->dead_lock);

		ft_usleep(philo->t_sleep);

		return;

	}

	pthread_mutex_unlock(philo->dead_lock);

}

// void	take_forks(t_phi *philo)	OG
// {
// 	pthread_mutex_lock(philo->l_fork);
// 	pthread_mutex_lock(philo->dead_lock);
// 	if (*philo->dead != 1)
// 		print_status(philo, "has taken a fork");
// 	pthread_mutex_unlock(philo->dead_lock);
// 	pthread_mutex_lock(philo->r_fork);
// 	pthread_mutex_lock(philo->dead_lock);
// 	if (*philo->dead != 1)
// 		print_status(philo, "has taken a fork");
// 	pthread_mutex_unlock(philo->dead_lock);
// }



// void    take_forks(t_phi *philo) -- last working version
// {
//     // Even philosophers take right fork first, odd take left fork first
//     // This helps prevent deadlocks and reduces competition
//     if (philo->id % 2 == 0)
//     {
//         pthread_mutex_lock(philo->r_fork);
//         print_status(philo, "has taken a fork");
//         pthread_mutex_lock(philo->l_fork);
//         print_status(philo, "has taken a fork");
//     }
//     else
//     {
//         ft_usleep(1); // Small delay for odd philosophers
//         pthread_mutex_lock(philo->l_fork);
//         print_status(philo, "has taken a fork");
//         pthread_mutex_lock(philo->r_fork);
//         print_status(philo, "has taken a fork");
//     }
// }

// void    take_forks(t_phi *philo)
// {
//     // Special case for 1 philosopher
//     if (philo->phi_num == 1)
//     {
//         pthread_mutex_lock(philo->l_fork);
//         print_status(philo, "has taken a fork");
//         return;
//     }

//     // For more than 1 philosopher
//     if (philo->id % 2 == 0)
//     {
//         pthread_mutex_lock(philo->r_fork);
//         print_status(philo, "has taken a fork");
//         pthread_mutex_lock(philo->l_fork);
//         print_status(philo, "has taken a fork");
//     }
//     else
//     {
//         pthread_mutex_lock(philo->l_fork);
//         print_status(philo, "has taken a fork");
//         pthread_mutex_lock(philo->r_fork);
//         print_status(philo, "has taken a fork");
//     }
// }

void    take_forks(t_phi *philo)
{
	if (philo->phi_num == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		return;
	}

	// Even philosophers take right fork first, odd take left fork first
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
		ft_usleep(1);  // Small delay to reduce contention
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		ft_usleep(1);  // Small delay to reduce contention
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
	}
}


// void	release_forks(t_phi *philo)
// {
// 	pthread_mutex_unlock(philo->r_fork);
// 	pthread_mutex_unlock(philo->l_fork);
// }

void    release_forks(t_phi *philo)
{
	if (philo->phi_num == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return;
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

// void	eat(t_phi *philo)
// {
// 	take_forks(philo);
// 	pthread_mutex_lock(philo->dead_lock);
// 	if (*philo->dead != 1)
// 	{
// 		print_status(philo, "is eating");
// 		pthread_mutex_lock(philo->meal_lock);
// 		philo->eating = 1;
// 		philo->last_meal = get_current_time();
// 		pthread_mutex_unlock(philo->meal_lock);
// 		pthread_mutex_unlock(philo->dead_lock);
// 		ft_usleep(philo->t_eat);
// 		update_meal_count(philo);
// 		pthread_mutex_lock(philo->meal_lock);
// 		philo->eating = 0;
// 		release_forks(philo);
// 		return ;
// 	}
// 	pthread_mutex_unlock(philo->dead_lock);
// 	release_forks(philo);
// }

// void    eat(t_phi *philo)
// {
//     take_forks(philo);
	
//     if (check_if_dead(philo))
//     {
//         release_forks(philo);
//         return;
//     }

//     print_status(philo, "is eating");
//     pthread_mutex_lock(philo->meal_lock);
//     philo->eating = 1;
//     philo->last_meal = get_current_time();
//     pthread_mutex_unlock(philo->meal_lock);
	
//     ft_usleep(philo->t_eat);
	
//     pthread_mutex_lock(philo->meal_lock);
//     philo->eating = 0;
//     philo->meals_eaten++;
//     pthread_mutex_unlock(philo->meal_lock);
	
//     release_forks(philo);
// }


void    eat(t_phi *philo)
{
	take_forks(philo);
	
	if (check_dead_flag(philo))
	{
		release_forks(philo);
		return;
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