/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:56:04 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/15 18:38:54 by ccarrace         ###   ########.fr       */
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
	// 	ft_usleep(philo->data->time_to_eat / 10);
    if (philo->data->no_of_philos == 1)
        return (just_one_philo(philo));
    while (1)
    {
        if (philo->data->somebody_died == true || philo->data->everybody_finished == true)
            break;
        else if (!philo->finished_all_meals)
        {
			if (philo->data->somebody_died == false)
			{
            	take_forks(philo);
				ft_eat(philo);
				ft_sleep_and_think(philo);
				// ft_sleep(philo);
				// ft_think(philo);
			}
        }
    }
    return (NULL);
}

static void	*just_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
	safe_print(philo, "has taken a fork");
    pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
	ft_usleep(philo->data->time_to_die);
	safe_print(philo, "died. End of simulation.");
	return (NULL);
}

static void	take_forks(t_philo *philo)
{
/* ODDS LEFT-HANDED, EVEN RIGHT-HANDED */
	// if (philo->data->somebody_died == true || philo->data->everybody_finished == true)
	// 	return ;
	// else if (philo->name % 2 != 0)
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

/* LAST PHILO LEFT_HANDED, RELEASE FIRST FORK IF SECOND IS NOT AVAILABLE */
	if (philo->data->somebody_died == true)
		return ;
	else if (philo->name == philo->data->no_of_philos)
	{
		pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
		if (philo->data->somebody_died == true)
		{
			pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
			return ;
		}			
		if (pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]) == 0 && \
				philo->data->somebody_died == false)
		{	
			// safe_print(philo, "has taken his LEFT fork");
			// safe_print(philo, "has taken his RIGHT fork");
			safe_double_print(philo, "has taken his LEFT fork", "has taken his RIGHT fork");
		}
		else
			pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]);			
		if (philo->data->somebody_died == true)
		{
			pthread_mutex_unlock(&philo->data->mutex_arr[philo->right_fork]);
			return ;
		}	
		if (pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]) == 0 && \
				philo->data->somebody_died == false)
		{
			// safe_print(philo, "has taken his RIGHT fork");
			// safe_print(philo, "has taken his LEFT fork");
			safe_double_print(philo, "has taken his RIGHT fork", "has taken his LEFT fork");
		}
		else
			pthread_mutex_unlock(&philo->data->mutex_arr[philo->right_fork]);
	}
}

static void	ft_eat(t_philo *philo)
{
	if (philo->data->somebody_died == false)
	{
		philo->is_busy_eating = true;
		philo->time_last_meal = ft_current_time();	
		safe_print(philo, "is eating");
		ft_usleep(philo->data->time_to_eat);
		// if (pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]) != 0)
			pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
		// if (pthread_mutex_lock(&philo->data->mutex_arr[philo->right_fork]) != 0)
			pthread_mutex_unlock(&philo->data->mutex_arr[philo->right_fork]);	
		philo->is_busy_eating = false;
		philo->meals_completed++;
		if (philo->meals_completed == philo->data->meals_needed)
			philo->finished_all_meals = true;
	}	
}

static void	ft_sleep_and_think(t_philo *philo)
{
	if (philo->data->somebody_died == true || philo->data->everybody_finished == true)
		return ;
	else
	{
		safe_print(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		if (philo->data->somebody_died == true || philo->data->everybody_finished == true)
			return;
		else
		{
			safe_print(philo, "is thinking");
			// // ft_usleep((philo->data->time_to_eat * 2) - philo->data->time_to_sleep);
			// if (philo->data->no_of_philos % 2 != 0)
			// {
			// 	// ft_usleep(philo->data->time_to_die - (philo->data->time_to_eat * 2) - philo->data->time_to_sleep);
			// 	ft_usleep((philo->data->time_to_eat * 2) - philo->data->time_to_sleep);
			// 	// printf("ft_usleep = %lu\n", (philo->data->time_to_die - (philo->data->time_to_eat * 2) - philo->data->time_to_sleep));				
			// }
		}
	}
}