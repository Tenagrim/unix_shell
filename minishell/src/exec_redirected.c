/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirected.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:53:04 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 14:39:19 by gshona           ###   ########.fr       */
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

static int	exec_builtin(int (*exec_func)(char *const argv[], t_env *env), char **av, int *fds, t_env *env)
{
	int		o_fds[2];
	int		ret;
	
	o_fds[0] = dup(0);
	o_fds[1] = dup(1);
	dup_fds(fds);
	ret = exec_func(av, env);
	close_fds(fds);
	dup2(o_fds[0], 0);
	dup2(o_fds[1], 1);
	env->last_code = (unsigned char)(ret);
	return (ret);
}

int		exec_redirected(int (*exec_func)(char *const argv[], t_env *env),char *exec_path, char **av, int *fds, t_env *env)
{
	int		pid;
	int		status;
	int		ret;
	int		sig;
	char	**nat;

	ret = 0;
	if (exec_func)
		return (exec_builtin(exec_func, av, fds, env));
	pid = fork();
 	signal(2, forked_signal_handler);
	signal(3, forked_signal_handler);
	if (!pid)
	{
		dup_fds(fds);
			nat = gen_native_env(env);
			ret = execve(exec_path, av, nat);
			free_env_native(nat);
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
	sig = WTERMSIG(status);
	ret = WEXITSTATUS(status);
	env->last_code = ret;
	//ft_printf("exited: [%d] status: [%d]\n", ret, status);
	if (sig == 3)
	{
		env->last_code = 131;
		print_error("Quit: 3\n");
	}
	if (sig == 2)
	{
		env->last_code = 130;
		write(2, "\n", 1);
	}
 	signal(2, signal_handler);
	signal(3, signal_handler);
	return (status);
}
