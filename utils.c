/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:34:17 by zrz               #+#    #+#             */
/*   Updated: 2025/02/12 21:40:24 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sources.h"

int ft_strlen(char *str)
{
    int i;

    if (str == NULL)
        return (0);
    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

static int ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int ft_atoi(char *str)
{
	int		res;
	int		sign;
	int		i;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
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
void    housekeeping(char *str, t_exe *exe, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    if(str)
    {
        write(2, str, ft_strlen(str));
        write(2, "\n",1);
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



// redesigned sleep function

/*  int ft_usleep(size_t milisecs)

    finer control over the usleep duration by repeatedly
    checking the elapsed time and yielding the CPU in
    small increments (500 microseconds). Also allows for
    more a precise "wake up"

    
*/

int ft_usleep(size_t milisecs)
{
    size_t  start;

    start = get_current_time();
    while ((get_current_time() - start) < milisecs)
        usleep(500);
    return (0);
}

/*  size_t get_current_time(void)

    gettimeofday function to get the current time of day,
    then convert this time into milliseconds by multiplying
    the seconds by 1000 and adding the microseconds divided by 1000.

    TLDR: returns curent time in miliseconds
*/

size_t get_current_time(void)
{
    struct timeval  time;

    if (gettimeofday(&time, NULL) == -1)
        write(2, "gettimeofday() error\n", 22);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
