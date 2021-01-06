/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirected.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:53:04 by gshona            #+#    #+#             */
/*   Updated: 2021/01/06 19:09:51 by tenagrim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <exec_args.h>
#include<sys/wait.h>

static void	close_fds(int *fds)
{
	if (fds[0] != 0)
		close(fds[0]);
	if (fds[1] != 1)
		close(fds[1]);
}

static int	exec_builtin(int (*exec_func)(char *const argv[], t_env *env),
		char **av, int *fds, t_env *env)
{
	int		o_fds[2];
	int		ret;

	o_fds[0] = dup(0);
	o_fds[1] = dup(1);
	if (fds[0] != 0)
		dup2(fds[0], 0);
	if (fds[1] != 1)
		dup2(fds[1], 1);
	ret = exec_func(av, env);
	close_fds(fds);
	dup2(o_fds[0], 0);
	dup2(o_fds[1], 1);
	env->last_code = (unsigned char)(ret);
	return (ret);
}

static void	child_part(char *exec_path, char **av, int *fds, char **nat)
{
	int ret;

	if (fds[0] != 0)
		dup2(fds[0], 0);
	if (fds[1] != 1)
		dup2(fds[1], 1);
	ret = execve(exec_path, av, nat);
	free_env_native(nat);
	print_error2(strerror(errno), exec_path);
	exit(ret);
}

static int	parent_part(int *fds, t_env *env)
{
	int	sig;
	int	status;

	wait(&status);
	close_fds(fds);
	sig = WTERMSIG(status);
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
	sig = WEXITSTATUS(status);
	env->last_code = (unsigned char)sig;
	return (status);
}

int			exec_redirected(t_exec_args *a, t_env *env)
{
	int		pid;
	int		status;
	char	**nat;

	if (a->exec_func)
		return (exec_builtin(a->exec_func, a->prog->arguments, a->fds, env));
	pid = fork();
	signal(2, forked_signal_handler);
	signal(3, forked_signal_handler);
	nat = gen_native_env(env);
	if (!pid)
		child_part(a->exec_path, a->prog->arguments, a->fds, nat);
	else if (pid < 1)
	{
		print_error("minishell: fork failed to start new process\n");
		close_fds(a->fds);
		return (-1);
	}
	status = parent_part(a->fds, env);
	signal(2, signal_handler);
	signal(3, signal_handler);
	free_env_native(nat);
	return (status);
}
