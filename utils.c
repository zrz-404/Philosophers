/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:34:17 by zrz               #+#    #+#             */
/*   Updated: 2025/02/17 20:57:27 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sources.h"

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	res;
	int	i;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

// housekeeping aka destroy mutexes n shIT
void	housekeeping(char *str, t_exe *exe, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&exe->write_lock);
	pthread_mutex_destroy(&exe->meal_lock);
	pthread_mutex_destroy(&exe->dead_lock);
	while (i < exe->philos[0].phi_num)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;
	size_t	elapsed;
	size_t	remaining;

	start = get_current_time();
	while (1)
	{
		elapsed = get_current_time() - start;
		if (elapsed >= milliseconds)
			break ;
		remaining = milliseconds - elapsed;
		if (milliseconds - elapsed > 5)
			usleep(500);
		else
			usleep(100);
	}
	return (0);
}

/*  size_t get_current_time(void)
	gettimeofday function to get the current time of day,
	then convert this time into milliseconds by multiplying
	the seconds by 1000 and adding the microseconds divided by 1000.
	TLDR: returns curent time in miliseconds
*/
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
