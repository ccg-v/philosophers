/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:06:51 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/15 23:43:20 by ccarrace         ###   ########.fr       */
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
	bool				is_busy_eating;
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
	bool				somebody_died;
	bool				everybody_finished;
	bool				simulation_is_over;
	unsigned long		start_time;
	t_philo				*philos_arr;
	pthread_t			doctor;
	pthread_mutex_t		*mutex_arr;
	pthread_mutex_t		printing_mutex;
	pthread_mutex_t		simulation_mutex;
}	t_data;

// initializing
bool			data_initialized(t_data *data, char **argv);
bool			philos_initialized(t_data *data);
bool			mutexes_initialized(t_data *data);

//	starting
int				create_philos(t_philo *philo, t_data *data);

// philo_routine
void 			*philo_routine(void *arg);

// health_checkup
void			*health_checkup(void *arg);

// printing
void		safe_print(t_philo *philo, char *str);
void		safe_death_print(t_data *data, char *str, int i);
void		safe_double_print(t_philo *philo, char *str1, char *str2);

// ft_utils
unsigned long	ft_current_time(void);
unsigned long	elapsed_time(t_data *data);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
void			ft_usleep(unsigned long lapse);

#endif
