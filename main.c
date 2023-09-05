/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:13:30 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/05 22:01:30 by ccarrace         ###   ########.fr       */
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
	int		i;

	if (argc < 5 || argc > 6)
		printf("Wrong number of args\n");
	else if (args_are_valid(argv) == false)
		printf("Args not valid (not number or negative)\n");
	else
	{
		if (data_initialized(&data, argv) == false)
			return (0);
		if (philos_initialized(&data) == false)
			return (0);
		if (mutexes_initialized(&data) == false)
			return (0);
	}
	create_philos(&philo, &data);
	free(data.philos_arr);
	free(data.mutex_arr);
	pthread_mutex_destroy(&data.printing_mutex);
	i = 0;
	while (i < data.no_of_philos)
	{
		pthread_mutex_destroy(&data.mutex_arr[i]);
		i++;
	}
	return (0);
}