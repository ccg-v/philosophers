/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:06:51 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/18 21:13:14 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

// enum e_boolean
// {
// 	FALSE,
// 	TRUE
// };

typedef struct s_data	t_data;

typedef struct s_args
{
	int					no_of_philos;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	int					meals_needed;
}	t_args;

typedef struct s_philo
{
	t_data				*data;
	int					name;
	int					left_fork;
	int					right_fork;	
}	t_philo;

typedef struct s_data
{
	t_philo				*philos_arr;
	pthread_mutex_t		*mutex_arr;
}	t_data;

// initializing
bool	parameters_initialized(t_args *args, char **argv);
// bool	data_initialized(t_args *args, t_data *data, t_philo *philo);
bool	philos_initialized(t_args *args, t_data *data);
bool	mutexes_initialized(t_args *args, t_data *data);

// ft_utils
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif
