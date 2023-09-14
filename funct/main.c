/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:13:30 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/14 22:00:42 by ccarrace         ###   ########.fr       */
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

// static bool	somebody_died(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->no_of_philos)
// 	{
// 		if (data->philos_arr[i].is_busy_eating == false && (ft_current_time() - data->philos_arr[i].time_last_meal) > data->time_to_die)
// 		{
// 			data->somebody_died = true;
// 			safe_death_print(data, "died. End of simulation.\n", i);
// 			return (true);
// 		}
// 		i = (i + 1) % (data->no_of_philos + 1);
// 	}
// 	return (false);
// }

// static 	everybody_finished(t_data *data)
// {
// 	int	i;
// 	int	philos_full = 0;

// 	i = 0;
// 	while (i < data->no_of_philos)
// 	{
// 		if (data->philos_arr[i].finished_all_meals == true)
// 			philos_full++;
// 		i = (i + 1) % (data->no_of_philos + 1);
// 	}
// 	if (philos_full == data->no_of_philos)
// 	{
// 		ft_usleep(data->time_to_die);
// 		pthread_mutex_lock(&data->printing_mutex);
// 		printf("%lu \tAll philosophers completed %d meals. End of simulation.\n", elapsed_time(data), data->meals_needed);
// 		pthread_mutex_unlock(&data->printing_mutex);
// 		data->everybody_finished = true;
// 		return (true);
// 	}
// 	return (false);
// }

static void	checker(t_data *data)
{
	int	i;
	int	philos_full;

	i = 0;
	philos_full = 0;
	while (1)
	{
		if (i < data->no_of_philos && data->philos_arr[i].finished_all_meals == true)
			philos_full++;
		if (philos_full == data->no_of_philos)
			{
				ft_usleep(data->time_to_die);
				pthread_mutex_lock(&data->printing_mutex);
				printf("%lu \tAll philosophers completed %d meals. End of simulation.\n", elapsed_time(data), data->meals_needed);
				pthread_mutex_unlock(&data->printing_mutex);
				data->everybody_finished = true;				
			}
		if (data->philos_arr[i].is_busy_eating == false && (ft_current_time() - data->philos_arr[i].time_last_meal) > data->time_to_die) 
		{
			data->somebody_died = true;
			safe_death_print(data, "died. End of simulation.\n", i);
		}
		if (data->everybody_finished || data->somebody_died)
            return;
		i = (i + 1) % (data->no_of_philos + 1);
	}
}

int	main(int argc, char **argv)
{	
	t_data	data;
	t_philo	philo;
	int		i;

	if (argc < 5 || argc > 6)
		printf("Wrong number of args\n");
	else if (args_are_valid(argv) == false)
		printf("Invalid arguments (must be positive numbers)\n");
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
	checker(&data);
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