/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:56:04 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/08 22:33:06 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*just_one_philo(t_philo *philo);
static void	take_forks(t_philo *philo);
static void	ft_eat(t_philo *philo);
static void	ft_sleep(t_philo *philo);
static void ft_think(t_philo *philo);

static void	ft_sleep_and_think(t_philo *philo);

void *philo_routine(void *arg)
{
    t_philo *philo;
    int i;

    philo = (t_philo *)arg;
    i = 0;
	// if ((philo->name % 2) == 0)
	// 	ft_usleep(philo->data->time_to_eat);
		// usleep(philo->data->time_to_eat * 1000);
    while (1)
    {
        if (philo->data->somebody_died == true || philo->data->everybody_finished == true)
            break;
        if (philo->data->no_of_philos == 1)
            return (just_one_philo(philo));
        else if (!philo->finished_all_meals)
        {
			if (philo->data->somebody_died == false)
			{
            	take_forks(philo);
				ft_eat(philo);
				ft_sleep_and_think(philo);
			}
            // ft_sleep(philo);
            // ft_think(philo);
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
//     while (philo->data->somebody_died == false && philo->data->everybody_finished == false)
//     {
//         if (philo->data->no_of_philos == 1)
// 			return(just_one_philo(philo));
//         else if (philo->data->somebody_died == false || (philo->data->meals_needed != -1 && philo->meals_completed < philo->data->meals_needed))
//         {
// 			// if (philo->data->somebody_died == false)
// 			// {
// 				if (philo->finished_all_meals == false)
// 				{
// 					take_forks(philo);
// 					ft_eat(philo);
// 					ft_sleep(philo);
// 					ft_think(philo);
// 				}
// 			// }
// 			if (philo->data->somebody_died == true|| philo->data->everybody_finished == true)
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
	// usleep(philo->data->time_to_die * 1000);
	// ft_usleep(philo->data->time_to_die);
	// safe_print(philo, "died");
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

	// if (philo->name == philo->data->no_of_philos)
	// {
	// 	pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
	// 	safe_print(philo, "has taken his LEFT fork");
	// 	pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]);
	// 	safe_print(philo, "has taken his RIGHT fork");
	// }
	// else
	// {
	// 	pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]);
	// 	safe_print(philo, "has taken his RIGHT fork");			
	// 	pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
	// 	safe_print(philo, "has taken his LEFT fork");
	// }

	if (philo->data->somebody_died == false)
	{
		if (philo->name == philo->data->no_of_philos)
		{
			pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
			if (pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]) == 0)
			{	safe_print(philo, "has taken his LEFT fork");
				safe_print(philo, "has taken his RIGHT fork");
			}
			else
				pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
		}
		else
		{
			pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]);			
			if (pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]) == 0)
			{
				safe_print(philo, "has taken his RIGHT fork");
				safe_print(philo, "has taken his LEFT fork");
			}
			else
				pthread_mutex_unlock(&philo->data->mutex_arr[philo->right_fork]);
		}
	}
}

static void	ft_eat(t_philo *philo)
{
	if (philo->data->somebody_died == false)
	{
		philo->is_busy_eating = true;
		philo->time_last_meal = ft_current_time();	
		safe_print(philo, "is eating");
		// usleep(philo->data->time_to_eat * 1000);
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->mutex_arr[philo->right_fork]);	

		philo->is_busy_eating = false;
		philo->meals_completed++;
		if (philo->meals_completed == philo->data->meals_needed)
			philo->finished_all_meals = true;
		// philo->time_last_meal = ft_current_time();
	}	
}

// static void	ft_sleep(t_philo *philo)
// {
// 	// if (philo->data->somebody_died == false)
// 	// {
// 		safe_print(philo, "is sleeping");
// 		// usleep(philo->data->time_to_sleep * 1000);
// 		ft_usleep(philo->data->time_to_sleep);
// 	// }
// }

// static void ft_think(t_philo *philo)
// {
// 	// if (philo->data->somebody_died == false)
// 		safe_print(philo, "is thinking");
// }

static void	ft_sleep_and_think(t_philo *philo)
{
	if (philo->data->somebody_died == false)
	{
		safe_print(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		safe_print(philo, "is thinking");
	}
}