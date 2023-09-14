/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:08:50 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/15 00:37:38 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(t_philo *philo, char *str)
{
	if (philo->data->somebody_died == true)
		return ;
	else
	{
		pthread_mutex_lock(&philo->data->printing_mutex);
		if (philo->data->somebody_died == true)
			return ;
		else		
			printf("%lu \t%d %s\n", elapsed_time(philo->data), philo->name, str);
		pthread_mutex_unlock(&philo->data->printing_mutex);
	}
}

void	safe_double_print(t_philo *philo, char *str1, char *str2)
{
	if (philo->data->somebody_died == true)
		return ;
	else
	{
		pthread_mutex_lock(&philo->data->printing_mutex);
		if (philo->data->somebody_died == true)
			return ;
		else
		{		
			printf("%lu \t%d %s\n", elapsed_time(philo->data), philo->name, str1);
			printf("%lu \t%d %s\n", elapsed_time(philo->data), philo->name, str2);			
		}
		pthread_mutex_unlock(&philo->data->printing_mutex);
	}
}

void	safe_death_print(t_data *data, char *str, int i)
{
	pthread_mutex_lock(&data->printing_mutex);
	printf("%lu \t%d %s\n", elapsed_time(data), data->philos_arr[i].name, str);
	pthread_mutex_unlock(&data->printing_mutex);
}

// void	safe_end_print(t_data *data, char *str)
// {
// 	pthread_mutex_lock(&data->printing_mutex);
// 	printf("%lu \t%d %s\n", elapsed_time(data), data->philos_arr[i].name, str);
// 	pthread_mutex_unlock(&data->printing_mutex);	
// }