/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:19:36 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 14:20:15 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			(*get_exec_func(char *name))(char *const argv[], t_env *env)
{
	if (!ft_strcmp("exit", name))
		return (exit_biultin);
	if (!ft_strcmp("echo", name))
		return (echo_biultin);
	if (!ft_strcmp("cd", name))
		return (cd_biultin);
	if (!ft_strcmp("pwd", name))
		return (pwd_biultin);
	if (!ft_strcmp("env", name))
		return (env_biultin);
	if (!ft_strcmp("export", name))
		return (export_biultin);
	if (!ft_strcmp("unset", name))
		return (unset_biultin);
	return (NULL);
}
