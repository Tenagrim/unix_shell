/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirected.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:53:04 by gshona            #+#    #+#             */
/*   Updated: 2020/12/28 22:02:03 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		exec_redirected(char *exec_path, char **av, int *fds, char **env)
{
	int	pid;
	int	status;
	int	ret;

	ret = 0;
	pid = fork();
	//ft_printf("fd_in: %d fd_out: %d\n", fd_in, fd_out);
	if (!pid)
	{
		if (fds[0] != 0)
			dup2(fds[0], 0);
		if (fds[1] != 1)
			dup2(fds[1], 1);
		ret = execve(exec_path, av, env);
		//ft_printf("error execve returned |%d|\n", ret);
		//printf("exec_path: %s\n", exec_path);
		ft_printf("minishell: %s: %s\n", exec_path, strerror(errno));
		exit(ret);
	}
	else
	{
		wait(&status);
		if (fds[0] != 0)
			close(fds[0]);
		if (fds[1] != 1)
			close(fds[1]);
	}
	return (status);
}
