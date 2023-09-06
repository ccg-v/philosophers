/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:55:06 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/03 21:21:53 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	data_initialized(t_data *data, char **argv)
{
	data->no_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->no_of_philos <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0\
		|| data->time_to_sleep <= 0)
		return (false);
	if (argv[5])
	{
		data->meals_needed = ft_atoi(argv[5]);
		if (data->meals_needed <= 0)
			return (false);
	}
	else
		data->meals_needed = -1;
	data->someone_died = false;
	data->everyone_finished = false;
	data->start_time = ft_current_time();
	return (true);
}

/*
	Smarter way of assigning forks to philos:
	i = 0;
	while (i < args->no_of_philos)
	{
		data->philos_arr[i].right_fork = i;
		data->philos_arr[i].left_fork = (i + 1) % args->no_of_philos;
		i++;
	}
	Remember a philosopher's 'left_fork' and 'right_fork' are the indexes we 
	are going to use to move within the array of mutexes and find which mutex
	corresponds to that philosopher's fork. Neighboring philosophers share
	the same fork, hence they share the same mutex.
*/
bool	philos_initialized(t_data *data)
{
	int	i;

	i = 0;
	data->philos_arr = malloc(sizeof(t_philo) * data->no_of_philos);
	if (!data->philos_arr)
		return (false);
	while(i < data->no_of_philos)
	{
		data->philos_arr[i].data = data;
		data->philos_arr[i].name = i + 1;
		data->philos_arr[i].meals_completed = 0;
		data->philos_arr[i].is_busy_eating = false;
		data->philos_arr[i].finished_all_meals = false;
		data->philos_arr[i].time_last_meal = ft_current_time();
// 		if (i == 0)
// 			data->philos_arr[i].right_fork = args->no_of_philos;
// 		else
// 			data->philos_arr[i].right_fork = i;
// 		data->philos_arr[i].left_fork = i + 1;
		data->philos_arr[i].right_fork = i;
		data->philos_arr[i].left_fork = (i + 1) % data->no_of_philos;
		i++;
	}
	return (true);
}

/* AM */
bool	mutexes_initialized(t_data *data)
{
	int	i;

	i = 0;
	data->mutex_arr = malloc(sizeof(pthread_mutex_t) * data->no_of_philos);
	if(!data->mutex_arr)
		return (false);
	while (i < data->no_of_philos)
	{
		pthread_mutex_init(&data->mutex_arr[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->printing_mutex, NULL);
	return (true);
}
