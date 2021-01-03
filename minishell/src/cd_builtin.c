/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:35:21 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 19:57:49 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	replace_or_create_env_variable(t_env *env, char *key, char *value)
{
	if (find_env_variable(env, key) == -1)
		add_env_variable(env, key, value);
	else
		replace_env_variable(env, key, value);
	return (0);
}

int			cd_biultin(char *const argv[], t_env *env)
{
	int		ret;
	char	*home;
	char	*pwd;
	char	*oldpwd;
	char	*path;

	ret = 1;
	path = argv[1];
	if (!argv[1])
	{
		if (!find_env_variable_cb(env, "HOME", &home))
			{
				print_error("minishell: cd: HOME not set\n");
				return (1);
			}
		path = home;
	}
	oldpwd = pwd_function();
	ret = chdir(path);
	pwd = pwd_function();
	if (ret)
	{
		print_error3("cd", argv[1], strerror(errno));
		free(pwd);
		free(oldpwd);
	}
	else
	{	
		replace_or_create_env_variable(env, "OLDPWD", oldpwd);
		replace_or_create_env_variable(env, "PWD", pwd);
	}
	return ((ret == 0) ? 0 : 1);
}
