/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:56:04 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/25 13:37:57 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*just_one_philo(t_philo *philo);
static void	ft_eat(t_philo *philo);
static void	ft_sleep_and_think(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	if (philo->name % 2 == 0)
		ft_usleep(philo->data->time_to_eat);
	if (philo->data->no_of_philos == 1)
		return (just_one_philo(philo));
	while (1)
	{
		if (philo->data->somebody_died == true \
		|| philo->data->everybody_finished == true)
			break ;
		take_forks(philo);
		ft_eat(philo);
		ft_sleep_and_think(philo);
	}
	return (NULL);
}

static void	*just_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
	safe_print(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
	ft_usleep(philo->data->time_to_die);
	return (NULL);
}

static void	ft_eat(t_philo *philo)
{
	if (philo->finished_all_meals == true || philo->data->somebody_died == true)
		return ;
	else if (philo->meals_completed != philo->data->meals_needed)
	{
		philo->is_busy_eating = true;
		philo->time_last_meal = ft_current_time();
		safe_print(philo, "is eating");
		philo->meals_completed++;
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->mutex_arr[philo->right_fork]);
		philo->is_busy_eating = false;
		if (philo->meals_completed == philo->data->meals_needed)
		{
			pthread_mutex_lock(&philo->data->printing_mutex);
			printf("%lu \t%d HAS COMPLETED ALL MEALS\n", elapsed_time(philo->data), \
				philo->name);
			pthread_mutex_unlock(&philo->data->printing_mutex);
			philo->finished_all_meals = true;
		}
	}
	return ;
}

static void	ft_sleep_and_think(t_philo *philo)
{
	if (philo->data->somebody_died == true \
			|| philo->data->everybody_finished == true)
		return ;
	safe_print(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	if (philo->data->somebody_died == false \
			&& philo->data->everybody_finished == false)
		safe_print(philo, "is thinking");
	if (philo->data->no_of_philos % 2 != 0)
		ft_usleep((philo->data->time_to_eat * 2) - philo->data->time_to_sleep);
}
