/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:13:30 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/21 00:29:57 by ccarrace         ###   ########.fr       */
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
	t_data	data;
	t_philo	philo;

	if (argc < 5 || argc > 6)
		printf("Wrong number of args\n");
	else if (args_are_valid(argv) == false)
		printf("Args not valid (not number or negative)\n");
	else
	{
		if (data_initialized(&data, argv) == false)
			return (0);
		// if (data_initialized(&adata, &data, &philo) == false)
		// 	return (0);
		if (philos_initialized(&data) == false)
			return (0);
		if (mutexes_initialized(&data) == false)
			return (0);
	}
	data.start_time = ft_current_time();
printf("start_time : %ld\n", data.start_time);
	int i = 0;
	while (i < data.no_of_philos)
	{
		printf("\nPhilosopher %d right fork is %d\n", data.philos_arr[i].name, data.philos_arr[i].right_fork);
		printf("Philosopher %d left fork is %d\n", data.philos_arr[i].name, data.philos_arr[i].left_fork);
		printf("\nPhilosopher %d right fork is %p\n", data.philos_arr[i].name, (void *)&data.mutex_arr[data.philos_arr[i].right_fork]);
		printf("Philosopher %d leftt fork is %p\n", data.philos_arr[i].name, (void *)&data.mutex_arr[data.philos_arr[i].left_fork]);	
		i++;
	}
	create_threads(&philo, &data);
	free(data.philos_arr);
	// free(data.forks_arr);
	return (0);
}