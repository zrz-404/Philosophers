/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:30:48 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/04 14:57:23 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sources.h"






// 4 or 5 arguments, not less, not more
/*
	*1 - phi N
	*2 - time it take phi to die if no eat
	*3 - time it takes phi to eat
	*4 - time it takes phi to sleep
	*5 - N times all philos need to eat before program stops
*/
int main(int argc, char **argv)
{
	t_runtime		runtime;
	t_phi			phi[PHILOS_MAX];
	pthread_mutex_t	forks[PHILOS_MAX];

	
}















// useful code snippets:



// void *function1();

// int main()
// {
// 	pthread_t thread1;

// 	pthread_create(&thread1, NULL, function1, NULL);
// 	/* 
// 	pos 1: passing a pointer to the thread
// 	pos 2: possible atributes to the thread
// 	pos 3: the function which will be run in the thread
// 	pos 4: when needed, arguments to pass to the function
// 	*/

// 	pthread_join(thread1, NULL);
// 	/*
// 	pos 1: the thread we want to join back with the main thread
// 	pos 2: can be used to work with the return value of the function
// 	*/
// 	return (0);
// }

// void *function1()
// {
// 	printf("function example\n");

// 	return NULL;
// }
