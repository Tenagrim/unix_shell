/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirected.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:53:04 by gshona            #+#    #+#             */
/*   Updated: 2020/12/29 17:49:00 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		close_fds(int *fds)
{
	if (fds[0] != 0)
		close(fds[0]);
	if (fds[1] != 1)
		close(fds[1]);
}

static void		dup_fds(int *fds)
{
	if (fds[0] != 0)
		dup2(fds[0], 0);
	if (fds[1] != 1)
		dup2(fds[1], 1);
}

//int				exec_redirected(char *exec_path, char **av, int *fds, char **env)
int		exec_redirected(int (*exec_func)(const char *path, char *const argv[], char *const envp[]),char *exec_path, char **av, int *fds, char **env)
{
	int	pid;
	int	status;
	int	ret;
	int	sig;

	ret = 0;
	if (exec_func == exit_biultin)
	{
		ret = exec_func(exec_path, av, env);
	}
	pid = fork();
 	signal(2, forked_signal_handler);
	signal(3, forked_signal_handler);
	if (!pid)
	{
		dup_fds(fds);
		ret = exec_func(exec_path, av, env);
		ft_printf("minishell: %s: %s\n", exec_path, strerror(errno));
		exit(ret);
	}
	else if (pid < 1)
	{
		print_error("minishell: fork failed to start new process\n");
		close_fds(fds);
		return (-1);
	}
	wait(&status);
	close_fds(fds);
	sig =  WTERMSIG(status);
	if (sig == 3)
		print_error("Quit: 3\n");
	if (sig == 2)
		write(2, "\n", 1);
 	signal(2, signal_handler);
	signal(3, signal_handler);
	return (status);
}
