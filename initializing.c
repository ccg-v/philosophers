/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:55:06 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/25 20:22:24 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	data_initialized(t_data *data, char **argv);
static int	philos_initialized(t_data *data);
static int	mutexes_initialized(t_data *data);

int	initialize_all(t_data *data, char **argv)
{
	if (!data_initialized(data, argv))
		return (0);
	if (!philos_initialized(data))
		return (0);
	if (!mutexes_initialized(data))
		return (0);
	return (1);
}

static int	data_initialized(t_data *data, char **argv)
{
	data->no_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->no_of_philos <= 0 || data->time_to_die <= 0 \
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (0);
	if (argv[5])
	{
		data->meals_needed = ft_atoi(argv[5]);
		if (data->meals_needed <= 0)
			return (0);
	}
	else
		data->meals_needed = -1;
	data->somebody_died = false;
	data->everybody_finished = false;
	data->start_time = ft_current_time();
	return (1);
}

static int	philos_initialized(t_data *data)
{
	int	i;

	i = 0;
	data->philos_arr = malloc(sizeof(t_philo) * data->no_of_philos);
	if (!data->philos_arr)
		return (0);
	while (i < data->no_of_philos)
	{
		data->philos_arr[i].data = data;
		data->philos_arr[i].name = i + 1;
		data->philos_arr[i].meals_completed = 0;
		data->philos_arr[i].is_busy_eating = false;
		data->philos_arr[i].finished_all_meals = false;
		data->philos_arr[i].time_last_meal = ft_current_time();
		data->philos_arr[i].right_fork = i;
		data->philos_arr[i].left_fork = (i + 1) % data->no_of_philos;
		i++;
	}
	return (1);
}

static int	mutexes_initialized(t_data *data)
{
	int	i;

	i = 0;
	data->mutex_arr = malloc(sizeof(pthread_mutex_t) * data->no_of_philos);
	if (!data->mutex_arr)
		return (0);
	while (i < data->no_of_philos)
	{
		pthread_mutex_init(&data->mutex_arr[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->printing_mutex, NULL);
	return (1);
}
