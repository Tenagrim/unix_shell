/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:35:21 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 18:45:34 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			cd_biultin(char *const argv[], t_env *env)
{
	int		ret;
	char	*home;
	char	*pwd;

	ret = 1;
	if (!argv[1])
	{
		if (!find_env_variable_cb(env, "HOME", &home))
			{
				print_error("minishell: cd: HOME not set\n");
				return (1);
			}
		ret = chdir(home);
	}
	else if (!is_dir(argv[1]))
	{
		print_error2("Not a directory", argv[1]);
		exit(1);
	}
	else
		ret = chdir(argv[1]);
	if (ret)
		print_error("ERROR CD\n");
	return ((ret == 0) ? 0 : 1);
}
