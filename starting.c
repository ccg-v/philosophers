/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:50:18 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/18 23:14:50 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_args *args, t_data *data)
{
	pthread_t	*pthread_arr;
	int			i;

	i = 0;
	pthread_arr = (pthread_t *)malloc(size_of(p_thread_t) * args->no_of_philos);
	if (!pthread_arr)
		return (-1);
	while (i < args->no_of_philos)
	{
		
	}
}