/*
	This function loops endlessly, but the i increases from '0' to
	'limit'. When 'i' is equal to 'limit' it is reset to '0' again
	so that its value will never be greater than 'limit'.
*/

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	(void)argc;
	int	i;
	int	limit;

	i = 0;
	limit = atoi(argv[1]);
	while (1)
	{
		printf("i = %d\n", i);
		i = (i + 1) % (limit + 1);
	}
	return (0);
}