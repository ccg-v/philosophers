/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:56:04 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/05 17:42:38 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*just_one_philo(t_philo *philo);
static void	take_forks(t_philo *philo);
static void	ft_eat(t_philo *philo);
static void	ft_sleep(t_philo *philo);
static void ft_think(t_philo *philo);

void *philo_routine(void *arg)
{
    t_philo *philo;
    int i;

    philo = (t_philo *)arg;
    i = 0;
	if ((philo->name % 2) == 0)
		usleep(philo->data->time_to_eat * 1000);
    while (1)
    {
        if (philo->data->someone_died || philo->data->everyone_finished)
            break;
        if (philo->data->no_of_philos == 1)
            return (just_one_philo(philo));
        else if (!philo->finished_all_meals)
        {
            take_forks(philo);
            ft_eat(philo);
            ft_sleep(philo);
            ft_think(philo);
        }
    }
    return (NULL);
}

// void *philo_routine(void *arg)
// {
//     t_philo *philo;
//     int i;

//     philo = (t_philo *)arg;
//     i = 0;
//     while (philo->data->someone_died == false && philo->data->everyone_finished == false)
//     {
//         if (philo->data->no_of_philos == 1)
// 			return(just_one_philo(philo));
//         else if (philo->data->someone_died == false || (philo->data->meals_needed != -1 && philo->meals_completed < philo->data->meals_needed))
//         {
// 			// if (philo->data->someone_died == false)
// 			// {
// 				if (philo->finished_all_meals == false)
// 				{
// 					take_forks(philo);
// 					ft_eat(philo);
// 					ft_sleep(philo);
// 					ft_think(philo);
// 				}
// 			// }
// 			if (philo->data->someone_died == true|| philo->data->everyone_finished == true)
//                 break;
//         }
//     }
//     return (NULL);
// }

static void	*just_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
	safe_print(philo, "has taken a fork");
    pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
	usleep(philo->data->time_to_die);
	// ft_usleep(philo->data->time_to_die);
	safe_print(philo, "died");
	return (NULL);
}

static void	take_forks(t_philo *philo)
{
// /*	Even take left fork first, odds take right fork first */
// 	if ((philo->name % 2) == 0)
// 	{
// 		// usleep(philo->data->time_to_eat * 1000);
// 		pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
// 		safe_print(philo, "has taken his LEFT fork");			
// 		pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]);
// 		safe_print(philo, "has taken his RIGHT fork");
// 	}
// 	else
// 	{
// 		usleep(philo->data->time_to_eat * 1000);
// 		pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]);
// 		safe_print(philo, "has taken his RIGHT fork");			
// 		pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
// 		safe_print(philo, "has taken his LEFT fork");		
// 	}
/* All philos take left fork first but last philo, that takes right fork first */	
	// if ((philo->name % 2) == 0)
	// 	usleep(philo->data->time_to_eat * 1000);
		// ft_usleep(philo->data->time_to_eat * 1000);
	if (philo->name == philo->data->no_of_philos)
	{
		pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
		safe_print(philo, "has taken his LEFT fork");			
		pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]);
		safe_print(philo, "has taken his RIGHT fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]);
		safe_print(philo, "has taken his RIGHT fork");			
		pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
		safe_print(philo, "has taken his LEFT fork");
	}
}

static void	ft_eat(t_philo *philo)
{
	philo->is_busy_eating = true;
	philo->time_last_meal = ft_current_time();	
	safe_print(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	// ft_usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
    pthread_mutex_unlock(&philo->data->mutex_arr[philo->right_fork]);	

	philo->is_busy_eating = false;
	philo->meals_completed++;
	if (philo->meals_completed == philo->data->meals_needed)
		philo->finished_all_meals = true;
	// philo->time_last_meal = ft_current_time();	
}

static void	ft_sleep(t_philo *philo)
{
	// if (philo->data->someone_died == false)
	// {
		safe_print(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		// ft_usleep(philo->data->time_to_sleep * 1000);
	// }
}

static void ft_think(t_philo *philo)
{
	// if (philo->data->someone_died == false)
		safe_print(philo, "is thinking");
}