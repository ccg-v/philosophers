#include <unistd.h>
#include <pthread.h>

void *function1(void *arg)
{
	pthread_mutex_t *writing_mutex = (pthread_mutex_t *)arg;

	pthread_mutex_lock(writing_mutex);
	int i = 0;
	while (i < 1000)
	{
		write(1, "|", 1);
		i++;
	}
	pthread_mutex_unlock(writing_mutex);

	return (NULL);
}

void *function2(void *arg)
{
	// pthread_mutex_t *writing_mutex = (pthread_mutex_t *)arg;

	// pthread_mutex_lock(writing_mutex);
	pthread_mutex_lock(arg);
	int i = 0;
	while (i < 1000)
	{
		write(1, "_", 1);
		i++;
	}	
	// pthread_mutex_unlock(writing_mutex);
	pthread_mutex_unlock(arg);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	pthread_mutex_t	writing_mutex;

	//	Initialize mutex
	pthread_mutex_init(&writing_mutex, NULL);

	//	Create threads
	pthread_create(&thread1, NULL, function1, &writing_mutex);
	pthread_create(&thread2, NULL, function2, &writing_mutex);

	//	Pthread_join blocks the execution of the calling thread (in this case,
	//	the main) until the target thread (thread1, thread2) finish.
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// destroy the mutex after it is no longer needed
	pthread_mutex_destroy(&writing_mutex);

	return (0);	
}

/*
	I tried to receive the mutex as a parameter in the functions:
		void *function1(pthread_mutex_t *writing_mutex)
	but the compiler does not accept it.

	The first function receives the mutex as 'arg' and typecasts it,
	but I thing its just a matter of readability, because the second
	function works without typecasting.
*/