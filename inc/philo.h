/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:06:51 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/21 00:29:50 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
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
	int					left_fork;
	int					right_fork;	
}	t_philo;

typedef struct s_data
{
	int					no_of_philos;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	int					meals_needed;
	bool				no_deaths;
	long int			start_time;
	t_philo				*philos_arr;
	pthread_mutex_t		*mutex_arr;
	pthread_mutex_t		printing_mutex;
}	t_data;

// initializing
bool			data_initialized(t_data *data, char **argv);
bool			philos_initialized(t_data *data);
bool			mutexes_initialized(t_data *data);

//	starting
int				create_threads(t_philo *philo, t_data *data);

// ft_utils
unsigned long	ft_current_time(void);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);

#endif
