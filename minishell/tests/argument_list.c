
#include <stdio.h>

int main(int ac, char *av[])
{
	while (*av)
	{
		printf("arg: |%s|\n", *av);
		av += 1;
	}
}

