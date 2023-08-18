#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long int ft_get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(long long time)
{
    time += ft_get_time();
    while (ft_get_time() <= time)
        usleep(200);
}

int main()
{
    printf("Starting program...\n");

    long long sleep_duration = 3000;  // Sleep for 3 milliseconds (3000 microseconds)
    printf("Current time: %ld\n", ft_get_time());

    ft_usleep(sleep_duration);

    printf("After sleeping for %lld microseconds.\n", sleep_duration);
    printf("Current time: %ld\n", ft_get_time());

    return 0;
}