#include <minishell.h>

char	*get_env_value(char **env, char *key)
{
	char	**p;
	char	*eq;
	int		len;

	p = env;
	len = ft_strlen(key);
	while (*p)
	{
		if(!(eq = ft_strchr(*p, '=')))
			return (NULL);
		if (!ft_strncmp(*p, key, len))
			return (eq + 1);
		p++;
	}
	return (0);
}

int		get_env(void *data, char *name, char **value)
{
	*value = get_env_value((char **)data, name);
	return (!!*value);
}

