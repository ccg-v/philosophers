/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_checkup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:03:46 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/16 00:03:31 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	somebody_died(t_data *data);
static bool	everybody_finished(t_data *data);

void	*health_checkup(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->simulation_mutex);
	if (data->simulation_is_over == true)
	{
		pthread_mutex_unlock(&data->simulation_mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&data->simulation_mutex);
	while (everybody_finished(data) == false)
	{
		if (somebody_died(data) == true)
			return (NULL);
		ft_usleep(10);
	}
	return (NULL);
}

static bool	everybody_finished(t_data *data)
{
	int	i;
	int	philos_full = 0;

	i = 0;
	if (data->meals_needed == -1)
		return (false);
	while (i < data->no_of_philos)
	{
		if (data->philos_arr[i].finished_all_meals == true)
			philos_full++;
		i++;
		// i = (i + 1) % (data->no_of_philos + 1);
	}
	if (philos_full == data->no_of_philos)
	{
		ft_usleep(data->time_to_die);
		pthread_mutex_lock(&data->printing_mutex);
		printf("\tAll philosophers completed %d meals. End of simulation.\n", data->meals_needed);
		pthread_mutex_unlock(&data->printing_mutex);
		data->everybody_finished = true;
		return (true);
	}
	return (false);
}

static bool	somebody_died(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philos)
	{
		if ((ft_current_time() - data->philos_arr[i].time_last_meal) > data->time_to_die \
			&& data->philos_arr[i].is_busy_eating == false \
			&& data->everybody_finished == false)
		{
			data->somebody_died = true;
			safe_death_print(data, "died. End of simulation.", i);
			return (true);
		}
		i = (i + 1) % (data->no_of_philos + 1);
	}
	return (false);
}
