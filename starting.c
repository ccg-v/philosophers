/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:50:18 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/03 13:48:37 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	ft_free()
// {
// 	printf("time to free whatever needs to be freed\n");
// 	return (0);
// }

static void	safe_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->printing_mutex);
	printf("%lu \t%d %s\n", elapsed_time(philo->data), philo->name, str);
	pthread_mutex_unlock(&philo->data->printing_mutex);
}

// static void	safe_count(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->meal_counter_mutex);
// 	philo->meals_completed++;		
//     pthread_mutex_unlock(&philo->data->meal_counter_mutex);
// }

static void	ft_sleep(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

static void ft_think(t_philo *philo)
{
	safe_print(philo, "is thinking");
}

static void	*just_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_arr[philo->left_fork]);
	safe_print(philo, "has taken a fork");
    pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
	usleep(philo->data->time_to_die);
	safe_print(philo, "died");
	return (NULL);
}

static void	take_forks(t_philo *philo)
{
	if ((philo->name % 2) == 0)
		usleep(philo->data->time_to_eat * 1000);
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

void *philo_routine(void *arg)
{
    t_philo *philo;
    int i;

    philo = (t_philo *)arg;
    i = 0;
    while (philo->data->someone_died == false && philo->data->everyone_finished == false)
    {
        if (philo->data->no_of_philos == 1)
			return(just_one_philo(philo));
        else if (philo->data->meals_needed != -1 && philo->meals_completed < philo->data->meals_needed)
        {
			take_forks(philo);
			safe_print(philo, "is eating");
			usleep(philo->data->time_to_eat * 1000);
            pthread_mutex_unlock(&philo->data->mutex_arr[philo->left_fork]);
            pthread_mutex_unlock(&philo->data->mutex_arr[philo->right_fork]);	

			// if (philo->data->meals_needed != -1)
			// {
				philo->meals_completed++;
				if (philo->meals_completed == philo->data->meals_needed)
					philo->finished_all_meals = true;
				philo->time_last_meal = ft_current_time();

				// pthread_mutex_lock(&philo->data->printing_mutex);
				// 	printf("%lu \t%d completed meal %d ..........\n", elapsed_time(philo->data), philo->name, philo->meals_completed);
				// pthread_mutex_unlock(&philo->data->printing_mutex);
			// }

			ft_sleep(philo);
			if (philo->finished_all_meals == false)
				ft_think(philo);
        }
    }
    return (NULL);
}

static bool	everybody_finished(t_data *data)
{
	int	i;
	int	philos_full = 0;

	i = 0;
	while (i < data->no_of_philos)
	{
		if (i == data->no_of_philos)
		{
			i = 0;
			philos_full = 0;
		}
		if (data->philos_arr[i].finished_all_meals == true)
			philos_full++;
		i++;
	}
	if (philos_full == data->no_of_philos)
	{
		printf("All philosophers completed %d meals. End of simulation.\n", data->meals_needed);
		data->everyone_finished = true;
		return (true);
	}
	return (false);
}

void	*health_checkup(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (data->meals_needed != -1 && everybody_finished(data) == true)
			return (NULL);
		usleep(10000);
	}
}

int	create_philos(t_philo *philo, t_data *data)
{
	pthread_t	*pthread_arr;
	int			i;

	i = 0;
	pthread_arr = (pthread_t *)malloc(sizeof(pthread_t) * data->no_of_philos);
	if (!pthread_arr)
		return (-1);
	while (i < data->no_of_philos)
	{
		if(pthread_create(&pthread_arr[i], NULL, &philo_routine, &data->philos_arr[i]) != 0)
			return (-1);	
		i++;
	}
	if (data->no_of_philos > 1)
	{
		if(pthread_create(&data->doctor, NULL, &health_checkup, data) != 0)
			return (-1);
	}
	i = 0;
	while (pthread_arr[i])
	{
		if (pthread_join(pthread_arr[i], NULL))
			return (-1);
		i++;
	}
	if (pthread_join(data->doctor, NULL) != 0)
		return (-1);
	free(pthread_arr);
	return (0);
}

// void *medical_checkup(void *arg)
// {
// 	t_data	*data;
// 	int		i;

// 	data = (t_data *)arg;
// 	i = 0;
// 	while (i < data->no_of_philos && data->philos_arr[i].meals_completed != data->meals_needed)
// 	{
// 		printf("data->philos[%d].meals_completed = %d\n", i, data->philos_arr[i].meals_completed);
// 		printf("data->meals_needed = %d\n", data->meals_needed);
// 		// if (data->philos_arr[i].meals_completed != data->meals_needed)
// 		// {
// 		// 	printf("Breaking loop...\n");
// 		// 	break;
// 		// }
// 		i++;
// 	}
// 	if (i == data->no_of_philos)
// 		printf("%lu \tAll philos completed %d meals. End of simulation.\n", \
// 			elapsed_time(data), data->meals_needed);
// 	return (0);
// }

// void	*medical_checkup(void *arg)
// {
// 	t_philo	*philo;
// 	int		i;

// 	philo = (t_philo *)arg;
// 	i = -1;
// 	// while (i < philo->data->no_of_philos && philo->data->someone_died == false)
// 	while (++i < philo->data->no_of_philos)
// 	{
// printf(".............. This is doctor ..............\n");
// 		if ((ft_current_time() - philo->data->philos_arr[i].time_last_meal) > philo->data->time_to_die)
// 		{
// 			// safe_print(philo, "DIED");
// 			// philo->data->someone_died = true;
// 			printf("%lu \tPHILO %d DIED!!!!!!!!!!!!!!!\n",elapsed_time(philo->data), philo->name);
// 			break;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// void	*medical_checkup(void *arg)
// {
// 	t_philo	*philo;
// 	int		i;

// 	philo = (t_philo *)arg;
// 	i = 1;
// 	while (i < philo->data->no_of_philos && (philo->data->someone_died == false && philo->data->everyone_finished == false))
// 	{
// 		if ((ft_current_time() - philo->data->philos_arr[i].time_last_meal) > philo->data->time_to_die)
// 		{
// 			safe_print(philo, "DIED");
// 			philo->data->someone_died = true;
// 		}
// 		else
// 		{
// 			if (philo->meals_completed < philo->data->meals_needed)
// 			{
// 				philo->data->everyone_finished = false;
// 				break;
// 			}
// 		}
// 		i++;
// 	}
// 	if (i == philo->data->no_of_philos)
// 	{
// 		philo->data->everyone_finished = true;
// 		pthread_mutex_lock(&philo->data->printing_mutex);
// 		printf("%lu \tPhilo %d completed %d meals. End of simulation.\n", elapsed_time(philo->data), \
// 					philo->name, philo->data->meals_needed);				
//         pthread_mutex_unlock(&philo->data->printing_mutex);
// 	}
// 	return (0);
// }
