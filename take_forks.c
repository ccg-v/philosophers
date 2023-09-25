/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:53:17 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/25 20:22:51 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_is_left_handed(t_philo *philo);
static void	philo_is_right_handed(t_philo *philo);

/* 
	take_forks()
	
	To avoid deedlocks:
	- Last philo is left-handed and, unlike the rest, he takes first his left fork
		and second, his right fork.
	- All philos release the first fork immediately if they find the second fork 
        is not available
*/
void	take_forks(t_philo *philo)
{
	if (philo->finished_all_meals == true || philo->data->somebody_died == true)
		return ;
	if (philo->name == philo->data->no_of_philos)
		philo_is_left_handed(philo);
	else
		philo_is_right_handed(philo);
}

static void	philo_is_left_handed(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
	if (philo->finished_all_meals == true || philo->data->somebody_died == true)
	{
		pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
		return ;
	}
	if (pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]) == 0 \
			&& philo->finished_all_meals == false \
			&& philo->data->somebody_died == false)
		safe_double_print(philo, "has taken his left fork", \
			"has taken his right fork");
	else
		pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
}

static void	philo_is_right_handed(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]);
	if (philo->finished_all_meals == true || philo->data->somebody_died == true)
	{
		pthread_mutex_unlock(&philo->data->mutex_arr[philo->right_fork]);
		return ;
	}
	if (pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]) == 0 \
			&& philo->finished_all_meals == false \
			&& philo->data->somebody_died == false)
		safe_double_print(philo, "has taken his right fork", \
			"has taken his left fork");
	else
		pthread_mutex_unlock(&philo->data->mutex_arr[philo->right_fork]);
}
