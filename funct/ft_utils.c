/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:10:29 by ccarrace          #+#    #+#             */
/*   Updated: 2023/09/05 19:55:28 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	ft_current_time

	Returns the current time at the precise moment when the function is called.
	'gettimeofday()' returns a 'struct timeval' structure that contains the 
	current time in seconds ('time.tv_sec') and microseconds('time.tv_usec') 
	since the Unix epoch starting point (January 1, 1970).

	ft_current_time returns the time in milliseconds, hence we must convert the
	two 'struct timeval' values to milliseconds. The returned value can be a 
	'long long int' type if we want to ensure that the function can handle a wide 
	range of time intervals (many years or even centuries). But ff we don't need 
	to deal such extremely long intervals, returning'long int' or 'unsigned long' 
	will be enough.

	Returning 'unsigned long' type, rather than pretending to avoid negative values
	from 'gettimeofday()' -which is never going to happen-, is a choice to enhance 
	semantic clarity and consistency with good coding practices. Using an unsigned
	type helps convey your intentions more clearly and prevents issues related to 
	negative values.

	A 'size_t' type also works fine but since its usually meant for sizes and counts
	it might be slightly misleading. The size of 'size_t' can vary depending on the
	system architecture, and it might no be sufficient to represent large intervals. 
*/
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
	return(ft_current_time() - data->start_time);
}

void	ft_usleep(unsigned long lapse)
{
	unsigned long	start;

	start = ft_current_time();
	while ((ft_current_time() - start) < lapse)
		usleep(lapse / 2);
}

// int	ft_usleep(size_t milliseconds)
// {
// 	size_t	start;
// 	start = ft_current_time();
// 	while ((ft_current_time() - start) < milliseconds)
// 		usleep(10);
// 	return (0);
// }

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
