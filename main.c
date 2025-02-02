/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:30:48 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/02 17:18:12 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sources.h"

void *function1();

int main()
{
	pthread_t thread1;

	pthread_create(&thread1, NULL, function1, NULL);
	/* 
	pos 1: passing a pointer to the thread
	pos 2: possible atributes to the thread
	pos 3: the function which will be run in the thread
	pos 4: when needed, arguments to pass to the function
	*/

	pthread_join(thread1, NULL);
	/*
	pos 1: the thread we want to join back with the main thread
	pos 2: can be used to work with the return value of the function
	*/
	return (0);
}

void *function1()
{
	printf("function example\n");

	return NULL;
}