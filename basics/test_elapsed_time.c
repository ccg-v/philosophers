#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
	unsigned long	start_time;
}	t_data;

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

int	main(void)
{
	int i = 0;
	t_data	*data = malloc(sizeof(t_data));
	if (!data)
		return (-1);

	data->start_time = ft_current_time();
		printf("start time   : %lu\n", data->start_time);
	while (i < 10)
	{
		usleep(1000);
		printf("current time : %lu | elapsed time : %lu\n", ft_current_time(), elapsed_time(data));
		i++;
	}
	return (0);
}