/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:06:51 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/25 20:23:26 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

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
	unsigned long		start_time;
	t_philo				*philos_arr;
	pthread_t			doctor;
	pthread_mutex_t		*mutex_arr;
	pthread_mutex_t		printing_mutex;
}	t_data;

// initializing
int				initialize_all(t_data *data, char **argv);

//	starting
int				start_simulation(t_data *data);

// philo_routine
void			*philo_routine(void *arg);

// take_forks
void			take_forks(t_philo *philo);

// health_checkup
void			*health_checkup(void *arg);

// printing
void			safe_print(t_philo *philo, char *str);
void			safe_double_print(t_philo *philo, char *str1, char *str2);
void			safe_death_print(t_data *data, char *str, int i);

// ft_utils
unsigned long	ft_current_time(void);
unsigned long	elapsed_time(t_data *data);
void			ft_usleep(unsigned long lapse);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);

#endif
