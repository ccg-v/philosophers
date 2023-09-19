/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:50:18 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/19 01:28:49 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_data *data)
{
	pthread_t	*philos_arr;
	int			i;

	i = -1;
	philos_arr = (pthread_t *)malloc(sizeof(pthread_t) * data->no_of_philos);
	if (!philos_arr)
		return (0);
	while (++i < data->no_of_philos)
	{
		if(pthread_create(&philos_arr[i], NULL, &philo_routine, &data->philos_arr[i]) != 0)
			return (0);	
	}
	if(pthread_create(&data->doctor, NULL, &health_checkup, data) != 0)
		return (0);
	i = -1;
	while (++i < data->no_of_philos)
	{
		if (pthread_join(philos_arr[i], NULL) != 0)
			return (0);
	}
	if (pthread_join(data->doctor, NULL) != 0)
		return (0);
	free(philos_arr);
	return (1);
}

// int	start_philos(t_data *data);
// int	start_doctor(t_data *data);
// int	join_threads(t_data *data);

// int start_simulation(t_data *data)
// {
// 	if (!start_philos(data))
// 		return (0);
// 	if (!start_doctor(data))
// 		return (0);
// 	if (!join_threads(data))
// 		return (0);
// 	return (1);
// }

// int	start_philos(t_data *data)
// {
// 	pthread_t	*threads_arr;
// 	int			i;

// 	i = 0;
// 	threads_arr = (pthread_t *)malloc(sizeof(pthread_t) * data->no_of_philos);
// 	if (!threads_arr)
// 		return (0);
// 	while (i < data->no_of_philos)
// 	{
// 		data->philos_arr[i].thread_id = threads_arr[i];
// 		i++;
// 	}
// 	i = 0;
// 	while (i < data->no_of_philos)
// 	{
// 		if(pthread_create(&data->philos_arr[i].thread_id, NULL, &philo_routine, &data->philos_arr[i]) != 0)
// 			return (0);	
// 		i++;
// 	}
// 	return (1);		
// }

// int	start_doctor(t_data *data)
// {
// 	if (data->no_of_philos > 1)
// 	{
// 		if(pthread_create(&data->doctor, NULL, &health_checkup, data) != 0)
// 			return (0);
// 	}
// 	return (1);	
// }

// int	join_threads(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->no_of_philos)
// 	{
// 		if (pthread_join(data->philos_arr[i].thread_id, NULL) != 0)
// 			return (0);
// 		i++;
// 	}
// 	if (pthread_join(data->doctor, NULL) != 0)
// 		return (0);
// 	return (1);
// }