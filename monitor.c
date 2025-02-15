/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:52:04 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/15 22:17:33 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// a function to print the required messages


// A function to check if a philosopher is dead


// check if any philosopher died (calls the prior function in it)


// Check if all the philosophers ate the number of meals assigned in the input


/* monitor the thread routine, something like this:
 
 void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	return (pointer);
}
*/
