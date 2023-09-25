/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:50:18 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/25 20:22:45 by ccarrace         ###   ########.fr       */
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
		if (pthread_create(&philos_arr[i], NULL, &philo_routine, \
		&data->philos_arr[i]) != 0)
			return (0);
	}
	if (pthread_create(&data->doctor, NULL, &health_checkup, data) != 0)
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
