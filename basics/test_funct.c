#include <unistd.h>

void function1()
{
	int i = 0;
	while (i < 100)
	{
		write(1, "|", 1);
		i++;
	}
}

void function2()
{
	int i = 0;
	while (i < 100)
	{
		write(1, "_", 1);
		i++;
	}	
}

int	main(void)
{
	function1();
	function2();
	return (0);
}