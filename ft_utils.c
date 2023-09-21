/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:10:29 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/20 21:22:05 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_current_time(void)
{
	struct timeval	time;
	unsigned long	current_time;
	unsigned long	current_seconds;
	unsigned long	current_microseconds;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	current_seconds = time.tv_sec;
	current_microseconds = time.tv_usec;
	current_time = (current_seconds * 1000) + (current_microseconds / 1000);
	return (current_time);
}

unsigned long	elapsed_time(t_data *data)
{
	return (ft_current_time() - data->start_time);
}

void	ft_usleep(unsigned long lapse)
{
	unsigned long	start;

	start = ft_current_time();
	while ((ft_current_time() - start) < lapse)
		usleep(lapse);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = (sign * -1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}
