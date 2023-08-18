/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:13:30 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/18 21:12:41 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	args_are_valid(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return(false);
			if ((ft_atoi(argv[i]) <= 0))
				return(false);
			j++;
		}
	}
	return (true);
}

int	main(int argc, char **argv)
{	
	t_args	args;
	t_data	data;
	t_philo	philo;

	if (argc < 5 || argc > 6)
		printf("Wrong number of args\n");
	else if (args_are_valid(argv) == false)
		printf("Args not valid (not number or negative)\n");
	else
	{
		if (parameters_initialized(&args, argv) == false)
			return (0);
		// if (data_initialized(&args, &data, &philo) == false)
		// 	return (0);
		if (philos_initialized(&args, &data) == false)
			return (0);
		if (mutexes_initialized(&args, &data) == false)
			return (0);
	}
	int i = 0;
	while (i < args.no_of_philos)
	{
		printf("\nPhilosopher %d right fork is %d\n", data.philos_arr[i].name, data.philos_arr[i].right_fork);
		printf("Philosopher %d left fork is %d\n", data.philos_arr[i].name, data.philos_arr[i].left_fork);
		printf("\nPhilosopher %d right fork is %p\n", data.philos_arr[i].name, (void *)&data.mutex_arr[data.philos_arr[i].right_fork]);
		printf("Philosopher %d leftt fork is %p\n", data.philos_arr[i].name, (void *)&data.mutex_arr[data.philos_arr[i].left_fork]);	
		i++;
	}
	free(data.philos_arr);
	// free(data.forks_arr);
	return (0);
}