/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:13:30 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/19 23:45:14 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	args_are_valid(char **argv)
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
				return (false);
			if ((ft_atoi(argv[i]) <= 0))
				return (false);
			j++;
		}
	}
	return (true);
}

static void	clear_table(t_data *data)
{
	int	i;

	free(data->philos_arr);
	free(data->mutex_arr);
	pthread_mutex_destroy(&data->printing_mutex);
	i = 0;
	while (i < data->no_of_philos)
	{
		pthread_mutex_destroy(&data->mutex_arr[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	philo;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of args\n");
		return (0);
	}
	else if (args_are_valid(argv) == false)
	{
		printf("Args not valid (must be positive integers!)\n");
		return (0);
	}
	if (!initialize_all(&data, argv))
		return (0);
	if (!start_simulation(&data))
		return (0);
	clear_table(&data);
	return (1);
}
