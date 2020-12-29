/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exec_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:40:01 by gshona            #+#    #+#             */
/*   Updated: 2020/12/29 17:05:47 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		is_builtin(char *name)
{
	if (!ft_strcmp("echo", name))
		return (1);
	return (0);
}

static char	*get_path_with_env(char **env, char *name)
{
	return(find_path(get_env_value(env, "PATH"), name));
}

static int		get_command_ex(void *builtin_table, char **env, char *name, char **res)
{
	char	*in_path;

	(void)builtin_table;
	if (is_builtin(name) || *name == '/' || *name == '.' || ft_strchr(name, '/'))
	{
		*res = ft_strdup(name);
		return (1);
	}
	if ((in_path = get_path_with_env(env, name)))
	{
		*res = in_path;
		return (1);
	}
	return (0);
}

int		replace_exec_path(char **value, char **env)
{
	char	*tmp;
	char	*repl;
	int		found;

	//printf(">>[%s]\n", env[0]);
	if ((found = get_command_ex(NULL, env, *value, &repl)))
	{
		tmp = *value;
		*value = repl;
		free(tmp);
		return (1);
	}
	return (0);
}
