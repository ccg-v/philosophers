/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_checkup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:03:46 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/11 19:32:02 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	somebody_died(t_data *data);
static bool	everybody_finished(t_data *data);

void	*health_checkup(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (data->meals_needed != -1 && everybody_finished(data) == true)
			break;
		else if (somebody_died(data) == true)
			break;
	}
	return (NULL);
}

static bool	somebody_died(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_of_philos)
	{
		if (data->philos_arr[i].is_busy_eating == false && (ft_current_time() - data->philos_arr[i].time_last_meal) > data->time_to_die && data->everybody_finished == false)
		{
			data->somebody_died = true;
			safe_death_print(data, "died. End of simulation. ::::::::::::::::::", i);
			return (true);
		}
		i = (i + 1) % (data->no_of_philos + 1);
	}
	return (false);
}

/*
	i = (i + 1) % (data->no_of_philos + 1);
	When 'i' reaches its maximum value ('no_of_philos') it is reset to '0'
*/
static bool	everybody_finished(t_data *data)
{
	int	i;
	int	philos_full = 0;

	i = 0;
	while (i < data->no_of_philos)
	{
		// if (i == data->no_of_philos)
		// {
		// 	i = 0;
		// 	philos_full = 0;
		// }
		if (data->philos_arr[i].finished_all_meals == true)
			philos_full++;
		// i++;
		i = (i + 1) % (data->no_of_philos + 1);
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
