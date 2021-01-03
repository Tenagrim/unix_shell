/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:51:46 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 14:20:50 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int		exec_commands(t_super *progs, t_env *env)
{
	int			i;
	int			**pipes;
	int			cur_pipe;
	t_program	*prog;
	int			inp_fd;
	int			fds[2];
	char		*exec_path;
	int			(*exec_func)(char *const argv[], t_env *env);

	pipes = make_pipes();
	cur_pipe = 0;
	i = 0;
	inp_fd = 0;
	while (i < progs->count)
	{
		prog = progs->programs + i;
		fds[0] = inp_fd;
		fds[1] = 1;
		inp_fd = 0;
		exec_path = ft_strdup(prog->arguments[0]);
		exec_func = get_exec_func(exec_path);
		if (!exec_func && !(replace_exec_path(&exec_path, env)))
		{
			print_error2("command not found", exec_path);
			free(exec_path);
			return (free_pipes(pipes, 1));
		}
		cur_pipe = !cur_pipe;
		if (prog->flags & C_PIPE)
		{
			pipe(pipes[cur_pipe]);
			fds[1] = pipes[cur_pipe][1];
			inp_fd = pipes[cur_pipe][0];
		}
		if (prog->flags & C_LFT_RDR)
			fds[0] = open(prog->redirect_filename[0], O_RDONLY);
		if (prog->flags & C_RT_RDR)
			fds[1] = open(prog->redirect_filename[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (prog->flags & C_RTT_RDR)
			fds[1] = open(prog->redirect_filename[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (prog->flags & C_PIPE && (prog->flags & C_RT_RDR || prog->flags & C_RTT_RDR))
			close(pipes[cur_pipe][1]);
		if (i != 0 && progs->programs[i - 1].flags & C_PIPE && prog->flags & C_LFT_RDR)
			close(pipes[!cur_pipe][0]);
		if (fds[0] == -1)
		{
			print_error2("No such file or directory", prog->redirect_filename[0]);
			return (free_pipes(pipes, 1));
		}
		exec_redirected(exec_func, exec_path, prog->arguments, fds, env);
		if (exec_path)
			free(exec_path);
		i++;
	}
	return (free_pipes(pipes, 0));
}
