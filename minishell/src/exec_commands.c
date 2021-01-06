/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:51:46 by gshona            #+#    #+#             */
/*   Updated: 2021/01/06 14:54:45 by tenagrim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <exec_args.h>

static int	**make_pipes(void)
{
	int	**res;

	res = (int**)malloc(sizeof(int*) * 2);
	res[0] = (int*)malloc(sizeof(int) * 2);
	res[1] = (int*)malloc(sizeof(int) * 2);
	return (res);
}

static int	free_pipes(int **pipes, int ret)
{
	free(pipes[0]);
	free(pipes[1]);
	free(pipes);
	return (ret);
}

static void	open_fds(t_super *progs, t_exec_args *a, int i)
{
	a->cur_pipe = !(a->cur_pipe);
	if (a->prog->flags & C_PIPE)
	{
		pipe(a->pipes[a->cur_pipe]);
		a->fds[1] = a->pipes[a->cur_pipe][1];
		a->inp_fd = a->pipes[a->cur_pipe][0];
	}
	if (a->prog->flags & C_LFT_RDR)
		a->fds[0] = open(a->prog->redirect_filename[0],
				O_RDONLY);
	if (a->prog->flags & C_RT_RDR)
		a->fds[1] = open(a->prog->redirect_filename[1],
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (a->prog->flags & C_RTT_RDR)
		a->fds[1] = open(a->prog->redirect_filename[1],
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (a->prog->flags & C_PIPE && (a->prog->flags & C_RT_RDR ||
				a->prog->flags & C_RTT_RDR))
		close(a->pipes[a->cur_pipe][1]);
	if (i != 0 && progs->programs[i - 1].flags & C_PIPE &&
			a->prog->flags & C_LFT_RDR)
		close(a->pipes[!(a->cur_pipe)][0]);
}

static int		preparations(t_super *progs, t_exec_args *a,
		t_env *env, int i)
{
	a->prog = progs->programs + i;
	a->fds[0] = a->inp_fd;
	a->fds[1] = 1;
	a->inp_fd = 0;
	a->exec_path = ft_strdup(a->prog->arguments[0]);
	a->exec_func = get_exec_func(a->exec_path);
	if (!(a->exec_func) && !(replace_exec_path(&(a->exec_path), env)))
	{
		print_error2("command not found", a->exec_path);
		free(a->exec_path);
		env->last_code = 127;
		return (free_pipes(a->pipes, 1));
	}
	open_fds(progs, a, i);
	if (a->fds[0] == -1)
	{
		print_error2("No such file or directory",
				a->prog->redirect_filename[0]);
		return (free_pipes(a->pipes, 1));
	}
	return (0);
}

int			exec_commands(t_super *progs, t_env *env)
{
	int			i;
	t_exec_args	a;

	a.pipes = make_pipes();
	a.cur_pipe = 0;
	i = 0;
	a.inp_fd = 0;
	while (i < progs->count)
	{
		if (preparations(progs, &a, env, i))
			return (1);
		exec_redirected(&a, env);
		if (a.exec_path)
			free(a.exec_path);
		i++;
	}
	return (free_pipes(a.pipes, 0));
}
