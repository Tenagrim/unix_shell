/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:51:46 by gshona            #+#    #+#             */
/*   Updated: 2020/12/28 19:14:51 by gshona           ###   ########.fr       */
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

int		exec_commands(t_super *progs, char **env)
{
	int			i;
	int			**pipes;
	int			cur_pipe;
	t_program	*prog;
	int			fds[2];
	char		*exec_path;

	pipes = make_pipes();
	cur_pipe = 0;
	i = 0;
	while (i < progs->count)
	{
		prog = progs->programs + i;
		fds[0] = 0;
		fds[1] = 1;
		exec_path = ft_strdup(prog->arguments[0]);
		if (!(replace_exec_path(&exec_path, env)))
		{
			ft_printf("minishell: %s: command not found\n", exec_path); //FIXME to stderr
			free(exec_path);
			return (free_pipes(pipes, 1));
		}
		//printf(">>> exec_path: %s\n", exec_path);
		//printf(">>> av[0]: %s\n", prog->arguments[0]);
		cur_pipe = !cur_pipe;
		//ft_printf("{%d}\n", cur_pipe);
		if (prog->flags & C_PIPE)
		{
			pipe(pipes[cur_pipe]);
			prog->fd[1] = pipes[cur_pipe][1];
			progs->programs[i + 1].fd[0] = pipes[cur_pipe][0];
			ft_printf("PIPE\n");
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
		//ft_printf(">>[%s] in: %d  out: %d\n", prog->arguments[0], prog->fd[0], prog->fd[1]);
		if (prog->fd[0] == -1)
		{
			ft_printf("minishell: %s: No such file or directory\n", prog->redirect_filename[0]); //FIXME to stderr
			return (free_pipes(pipes, 1));
		}
		exec_redirected(exec_path, prog->arguments, fds, env);
		i++;
	}
	free(exec_path);
	return (free_pipes(pipes, 0));
}

