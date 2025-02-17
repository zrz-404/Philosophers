/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sources.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:31:08 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/17 17:44:47 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOURCES_H
# define SOURCES_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILOS_MAX 300

typedef struct s_phi
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			t_die;	// time it takes to die
	size_t			t_eat;	// time it takes to eat
	size_t			t_sleep;// time it takes to sleep
	size_t			start_time;
	int				phi_num;
	int				n_eat;	// number of times to eat
	int				*dead;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_phi;

typedef struct s_exe
{
	int				f_dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_phi			*philos;
}	t_exe;



// declarations
int		ft_atoi(char *str);
int		ft_strlen(char *str);
size_t	get_current_time(void);
int		ft_usleep(size_t milisecs);
void    housekeeping(char *str, t_exe *exe, pthread_mutex_t *forks);

// inits
void init_philos(t_phi *phi, t_exe *exe, pthread_mutex_t *forks, char **argv);
void init_struct(t_exe *exe, t_phi *philos);
void init_forks(pthread_mutex_t *forks, int phi_num);

// routine actions
void	print_status(t_phi *philo, char *msg);

void	think(t_phi *philo);
void	sleeping(t_phi *philo);
void	eat(t_phi *philo);
void	take_forks(t_phi *philo);
void    release_forks(t_phi *philo);
void	update_meal_count(t_phi *philo);

// threads
int		check_if_dead(t_phi *philo);
int		check_dead_flag(t_phi *philo);
void	*philo_routine(void *pointer);
int		create_threads(t_phi *philos, t_exe *exe);
void	*monitor_routine(void	*pointer);

#endif	// SOURCES_H

/*
 *	A philosopher will try to grab a fork?chopstick by executing a wait() operation
 *	on that semaphore (which represents a fork)
 *
 *	he releases said fork by executing signal() on the semaphores being acted upon
 *
 *	the shared data are
 *	
 *		semaphore fork[n];
 *	
 *	where all elements of 'fork' are initialized to one

*/
