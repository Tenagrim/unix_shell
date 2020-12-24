#include <minishell.h>

char	**copy_env(char **env)
{
	char	**res;
	int		count;
	int		i;

	count = 0;
	while (env[count++]);
	ft_printf(">>%d\n", count);
	res = (char**)malloc(sizeof(char*) * (count));
	res[count - 1] = NULL;
	i = -1;
	while (i++ < count - 2)
		res[i] = ft_strdup(env[i]);
	return (res);
}
