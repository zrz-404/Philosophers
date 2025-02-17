/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:30:48 by jroseiro          #+#    #+#             */
/*   Updated: 2025/02/17 21:01:11 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sources.h"

// check if inputs are numeric
static int	check_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

// check if the input is correct
int	check_valid_args(char **argv)
{
	if (ft_atoi(argv[1]) > PHILOS_MAX || ft_atoi(argv[1]) <= 0
		|| check_content(argv[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(argv[2]) <= 0 || check_content(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || check_content(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || check_content(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_content(argv[5]) == 1))
		return (write(2, "Invalid number of meals\n",
				51), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_exe			exe;
	t_phi			phi[PHILOS_MAX];
	pthread_mutex_t	forks[PHILOS_MAX];

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count.\n", 23));
	if (check_valid_args(argv) == 1)
		return (1);
	init_struct(&exe, phi);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(phi, &exe, forks, argv);
	if (create_threads(phi, &exe) != 0)
	{
		housekeeping("Error creating threads", &exe, forks);
		return (1);
	}
	housekeeping(NULL, &exe, forks);
	return (0);
}
