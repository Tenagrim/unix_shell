/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:35:21 by gshona            #+#    #+#             */
/*   Updated: 2021/01/07 12:33:50 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	replace_or_create_env_variable(t_env *env, char *key, char *value)
{
	add_env_variable(env, key, value);
	return (0);
}

static int	return_err(void)
{
	print_error("minishell: cd: HOME not set\n");
	return (1);
}

static void	replace_pwds(t_env *env, char *pwd, char *oldpwd)
{
	replace_or_create_env_variable(env, "OLDPWD", oldpwd);
	replace_or_create_env_variable(env, "PWD", pwd);
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
		if (!find_env_variable_cb_static(env, "HOME", &home))
			return (return_err());
		path = home;
	}
	oldpwd = pwd_function();
	ret = chdir(path);
	pwd = pwd_function();
	if (ret)
		print_error3("cd", argv[1], strerror(errno));
	else
		replace_pwds(env, pwd, oldpwd);
	free(pwd);
	free(oldpwd);
	return ((ret == 0) ? 0 : 1);
}
