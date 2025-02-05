/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:34:17 by zrz               #+#    #+#             */
/*   Updated: 2025/02/05 23:09:14 by zrz              ###   ########.fr       */
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

int ft_atoi(char *str)
{

}


    // housekeeping




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

    start = get_current_time;
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