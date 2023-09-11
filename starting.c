/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:50:18 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/11 22:25:00 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_philo *philo, t_data *data)
{
	pthread_t	*philos_arr;
	int			i;

	i = 0;

	philos_arr = (pthread_t *)malloc(sizeof(pthread_t) * data->no_of_philos);
	if (!philos_arr)
		return (-1);
	while (i < data->no_of_philos)
	{
		if(pthread_create(&philos_arr[i], NULL, &philo_routine, &data->philos_arr[i]) != 0)
			return (-1);	
		i++;
	}
	if (data->no_of_philos > 1)
	{
		if(pthread_create(&data->doctor, NULL, &health_checkup, data) != 0)
			return (-1);
	}
	i = 0;
	while (i < data->no_of_philos)
	{
		if (pthread_join(philos_arr[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(data->doctor, NULL) != 0)
		return (-1);
	free(philos_arr);
	return (0);
}
