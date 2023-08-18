/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:55:06 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/18 22:02:46 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	parameters_initialized(t_args *args, char **argv)
{
	args->no_of_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (args->no_of_philos <= 0 || args->time_to_die <= 0 || args->time_to_eat <= 0\
		|| args->time_to_sleep <= 0)
		return (false);
	if (argv[5])
	{
		args->meals_needed = ft_atoi(argv[5]);
		if (args->meals_needed <= 0)
			return (false);
	}
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
bool	philos_initialized(t_args *args, t_data *data)
{
	int	i;

	i = 0;
	data->philos_arr = malloc(sizeof(t_philo) * args->no_of_philos);
	if (!data->philos_arr)
		return (false);
	while(i < args->no_of_philos)
	{
		data->philos_arr[i].data = data;
		data->philos_arr[i].name = i + 1;
// printf("\nphilo[%d] name is %d\n", i, data->philos_arr[i].name);
// 		if (i == 0)
// 			data->philos_arr[i].right_fork = args->no_of_philos;
// 		else
// 			data->philos_arr[i].right_fork = i;
// printf("philo[%d] right fork is %d\n", i, data->philos_arr[i].right_fork);
// 		data->philos_arr[i].left_fork = i + 1;
// printf("philo[%d] left fork is %d\n", i, data->philos_arr[i].left_fork);
		data->philos_arr[i].right_fork = i;
		data->philos_arr[i].left_fork = (i + 1) % args->no_of_philos;
printf("philo[%d] right fork is %d\n", i, data->philos_arr[i].right_fork);
printf("philo[%d] left fork is %d\n", i, data->philos_arr[i].left_fork);
		i++;
	}
	return (true);
}

/* AM */
bool	mutexes_initialized(t_args *args, t_data *data)
{
	int	i;

	i = 0;
	data->mutex_arr = malloc(sizeof(pthread_mutex_t) * args->no_of_philos);
	if(!data->mutex_arr)
		return (false);
	while (i < args->no_of_philos)
	{
		pthread_mutex_init(&data->mutex_arr[i], NULL);
printf("mutex %d created\n", i);
		i++;
	}
	return (true);
}

/* JA */
// bool	forks_and_mutexes_initialized(t_args *args, t_data *data)
// {
// 	int	i;

// 	data->mutex_arr = malloc(sizeof(pthread_mutex_t) * args->no_of_philos);
// 	if(!data->mutex_arr)
// 		return (false);
// 	i = -1;
// 	while (++i < args->no_of_philos)
// 		pthread_mutex_init(&data->mutex_arr[i], NULL);
// 	i = 0;
// 	while (i < args->no_of_philos)
// 	{
// 		if (i == 0)
// 		{
// 			data->philos_arr[i].right_fork = &data->mutex_arr[args->no_of_philos - 1]; 
// printf("\nAssigning mutex_arr[%d] as right_fork to philo[%d]\n", args->no_of_philos - 1, i);
// 		}
// 		else if (i > 0)
// 		{
// 			data->philos_arr[i].right_fork = &data->mutex_arr[i - 1];
// printf("\nAssigning mutex_arr[%d] as right_fork to philo[%d]\n", i - 1, i);
// 		}
// 		data->philos_arr[i].left_fork = &data->mutex_arr[i];
// printf("Assigning mutex_arr[%d] as left_fork to philo[%d]\n", i, i);
// 		i++;
// 	}
// 	return (true);
// }

/* MINE */
// bool	forks_and_mutexes_initialized(t_args *args, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	data->mutex_arr = malloc(sizeof(pthread_mutex_t) * args->no_of_philos);
// 	if(!data->mutex_arr)
// 		return (false);
// 	while (i < args->no_of_philos)
// 	{
// 		pthread_mutex_init(&data->mutex_arr[i], NULL);
// 		data->philos_arr[i].right_fork = &data->mutex_arr[i];
// printf("\nAssigning mutex_arr[%d] as right_fork to philo[%d]\n", i, i);
// 		data->philos_arr[i].left_fork = &data->mutex_arr[(i + 1) % args->no_of_philos];
// printf("Assigning mutex_arr[%d] as left_fork to philo[%d]\n", (i + 1) % args->no_of_philos, i);

// 		i++;
// 	}
// 	return (true);
// }


// bool	data_initialized(t_args *args, t_data *data, t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	data->philos_arr = malloc(sizeof(t_philo) * args->no_of_philos);
// 	if (!data->philos_arr)
// 		return (false);
// 	data->forks_arr = malloc(sizeof(int) * args->no_of_philos);
// 	if(!data->forks_arr)
// 		return (false);
// 	while (i < args->no_of_philos)
// 		data->forks_arr[i] = i + 1;
// 	return (true);
// }
