/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:50:18 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/22 20:13:53 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	ft_free()
// {
// 	printf("time to free whatever needs to be freed\n");
// 	return (0);
// }

void	*thread_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	// while(philo->data->no_deaths == true)
	while (i < 10)
	{
		pthread_mutex_lock(&philo->data->printing_mutex);
		if (philo->data->no_of_philos == 1)
			printf("philo %d sat alone and 'i' is %d\n", philo->name, i);
		else
			printf("philo %d sat at the table and 'i' is %d\n", philo->name, i);
		pthread_mutex_unlock(&philo->data->printing_mutex);
		usleep(15);
		// pthread_mutex_lock(&philo->data->i_mutex);
		i++;
		// pthread_mutex_unlock(&philo->data->i_mutex);
	}
	// pthread_mutex_destroy(&philo->data->printing_mutex);
	return (0);
}

int	create_threads(t_philo *philo, t_data *data)
{
	pthread_t	*pthread_arr;
	int			i;

	i = 0;
	pthread_arr = (pthread_t *)malloc(sizeof(pthread_t) * data->no_of_philos);
	if (!pthread_arr)
		return (-1);
	while (i < data->no_of_philos)
	{
		if(pthread_create(&pthread_arr[i], NULL, &thread_routine, &data->philos_arr[i]) != 0)
			return (-1);
		i++;
	}
	// if (data->no_of_philos == 1)
	// {
	// 	pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
	// 	pthread_mutex_lock(&data->printing_mutex);
	// 	if (data->no_deaths == true)
	// 		printf("%lu philo %d has taken a fork\n", elapsed_time(data), 0);
	// 	pthread_mutex_unlock(&data->printing_mutex);
	// 	pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
	// }
	i = 0;
	while (pthread_arr[i])
	{
		pthread_join(pthread_arr[i], NULL);
		i++;
	}
	free(pthread_arr);
	return (0);
}
