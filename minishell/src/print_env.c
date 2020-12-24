#include <minishell.h>

void	print_env(char **env)
{
	char **p;

	p = env;
	while (*p)
	{
		write(1, *p, ft_strlen(*p));
		write(1, "\n", 1);
		p++;
	}
}


