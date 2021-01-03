#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return (-1);
	return (atoi(av[1]));
}
