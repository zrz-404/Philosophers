/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:48:25 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/12 00:19:04 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sources.h"

void	init_arguments(t_phi *philos, char **argv)
{
	philos->phi_num = ft_atoi(argv[1]);
	philos->t_die = ft_atoi(argv[2]);
	philos->t_eat = ft_atoi(argv[3]);
	philos->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philos->n_eat = ft_atoi(argv[5]);
	else
		philos->n_eat = -1;
}

void	init_philos(t_phi *phi, t_exe *exe, pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		phi[i].id = i + 1;
		phi[i].eating = 0;
		phi[i].meals_eaten = 0;
		init_arguments(&phi[i], argv);
		phi[i].start_time = get_current_time();
		phi[i].last_meal = get_current_time();
		phi[i].write_lock = &exe->write_lock;
		phi[i].dead_lock = &exe->dead_lock;
		phi[i].meal_lock = &exe->f_dead;
		phi[i].l_fork = &forks[i];
		if (i == 0)
			phi[i].r_fork = &forks[phi[i].phi_num - 1];
		else
			phi[i].r_fork = &forks[i - 1];
		i++;
	}
}

