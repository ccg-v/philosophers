#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data
{
	int					no_of_philos;
	int					*philos_arr;
	pthread_mutex_t		printing_mutex;
}	t_data;

void	*thread_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->no_of_philos)
	{
		pthread_mutex_lock(&data->printing_mutex);
		printf("philo %d sat at the table\n", data->philos_arr[i]);
		pthread_mutex_unlock(&data->printing_mutex);
		usleep(10);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{	
	t_data		data;
	int			i;
	pthread_t	*pthread_arr;

	pthread_arr = NULL;
	if (argc != 2)
		printf("ERROR: Please provide the number of philosophers (and nothing else)\n");
	else
	{
		data.no_of_philos = atoi(argv[1]);
		data.philos_arr = (int *)malloc(sizeof(int) * data.no_of_philos);
		if (!data.philos_arr)
			return (-1);
		pthread_mutex_init(&data.printing_mutex, NULL);
		i = 0;
		while(i < data.no_of_philos)
		{
			data.philos_arr[i] = i;
			i++;
		}
		pthread_arr = (pthread_t *)malloc(sizeof(pthread_t) * data.no_of_philos);
		if (!pthread_arr)
			return (-1);
		i = 0;
		while(i < data.no_of_philos)
		{		
			pthread_create(&pthread_arr[i], NULL, &thread_routine, &data);			
			i++;
		}
		i = 0;
		while(i < data.no_of_philos)
		{			
			pthread_join(pthread_arr[i], NULL);
			i++;
		}
		free(data.philos_arr);
		free(pthread_arr);
		pthread_mutex_destroy(&data.printing_mutex);
	}
	return (0);
}

