/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exec_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:40:01 by gshona            #+#    #+#             */
/*   Updated: 2021/01/07 17:44:48 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_path_with_env(t_env *env, char *name)
{
	char	*path;
	char	*res;

	if (!find_env_variable_cb_static(env, "PATH", &path))
		return (NULL);
	res = find_path(path, name);
	return (res);
}

static int	get_command_ex(void *builtin_table, t_env *env,
		char *name, char **res)
{
	char	*in_path;

	(void)builtin_table;
	if (ft_strchr(name, '/'))
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

int			replace_exec_path(char **value, t_env *env)
{
	char	*tmp;
	char	*repl;
	int		found;

	if ((found = get_command_ex(NULL, env, *value, &repl)))
	{
		tmp = *value;
		*value = repl;
		free(tmp);
		return (1);
	}
	return (0);
}
