/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:55:07 by gshona            #+#    #+#             */
/*   Updated: 2020/12/29 17:05:09 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		exec_command(char **av, char **env)
{
	int	pid;
	int	status;
	int	ret;

	ret = 0;
	pid = fork();
	if (!pid)
	{
		//ft_printf(">>> %s\n", av[0]);
		ret = execve(av[0], av, env);
		ft_printf("execve returned: %d\n", ret);
		exit(ret);
	}
	else
	{
		//ft_printf("start wait\n");
		wait(&status);
		//ft_printf("end wait\n");
	}
	return (ret);
}
