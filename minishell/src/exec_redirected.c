/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirected.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:53:04 by gshona            #+#    #+#             */
/*   Updated: 2020/12/27 14:53:16 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		exec_redirected(char **av, int fd_in, int fd_out, char **env)
{
	int	pid;
	int	status;
	int	ret;

	ret = 0;
	pid = fork();
	if (!pid)
	{
		if (fd_in != 0)
			dup2(fd_in, 0);
		if (fd_out != 1)
			dup2(fd_out, 1);
		ret = execve(av[0], av, env);
		exit(ret);
	}
	else
	{
		wait(&status);
		if (fd_in != 0)
			close(fd_in);
		if (fd_out != 1)
			close(fd_out);
	}
	return (ret);
}
