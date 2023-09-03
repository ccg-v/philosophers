/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:06:51 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/03 11:52:19 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>	//	write
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

// enum e_boolean
// {
// 	FALSE,
// 	TRUE
// };

typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data				*data;
	int					name;
	int					meals_completed;
	bool				finished_all_meals;
	unsigned long		time_last_meal;
	int					left_fork;
	int					right_fork;	
}	t_philo;

typedef struct s_data
{
	int					no_of_philos;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					meals_needed;
	bool				someone_died;
	bool				everyone_finished;
	unsigned long		start_time;
	t_philo				*philos_arr;
	pthread_t			doctor;
	pthread_mutex_t		*mutex_arr;
	pthread_mutex_t		printing_mutex;
	pthread_mutex_t		meal_counter_mutex;
}	t_data;

// initializing
bool			data_initialized(t_data *data, char **argv);
bool			philos_initialized(t_data *data);
bool			mutexes_initialized(t_data *data);

//	starting
int				create_philos(t_philo *philo, t_data *data);
// void			check_finish(t_data *data);

// ft_utils
unsigned long	ft_current_time(void);
unsigned long	elapsed_time(t_data *data);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				ft_usleep(size_t milliseconds);

// void	ft_usleep(long long time);

#endif
