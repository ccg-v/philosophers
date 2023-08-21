/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:50:18 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/21 00:28:30 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	ft_free()
// {
// 	printf("time to free whatever needs to be freed\n");
// 	return (0);
// }

int	thread_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	if (philo->name )
}

int	create_threads(t_philo *philo, t_data *data)
{
	pthread_t	*pthread_arr;
	int			i;

	i = 0;
	pthread_arr = (pthread_t *)malloc(size_of(pthread_t) * data->no_of_philos);
	if (!pthread_arr)
		return (-1);
	while (i < data->no_of_philos)
	{
		if(pthread_create(&data->philos_arr[i], NULL, &thread_routine, \
		&data->philos_arr[i]) != 0)
			return (ft_free());
		i++;
	}
	if (data->no_of_philos == 1)
	{
printf("::::::We are HERE\n");
		pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
		pthread_mutex_lock(&data->printing_mutex);
		if (data->no_deaths = true)
			printf("%ld philo %d has taken a fork\n", ft_current_time - \
			data->start_time , 0);
		pthread_mutex_unlock(&data->printing_mutex);
		pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
	} 
}