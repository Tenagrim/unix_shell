/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:51:46 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 12:56:30 by gshona           ###   ########.fr       */
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

int			exit_biultin(char *const argv[], t_env *env)
{
	(void)argv;
	(void)env;
	print_error("exit\n");
	exit(0);
}

int			echo_biultin(char *const argv[], t_env *env)
{
	char	min_n;
	int		i;
	(void)env;

	i = 1;
	min_n = 0;
	if (argv[1] && !ft_strcmp("-n", argv[1]))
	{
		i++;
		min_n = 1;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		write(1, " ", 1);
		i++;
	}
	if (!min_n)
		write(1, "\n", 1);
	return (0);
}

static	void	print_error2(char *error, char  *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

int			cd_biultin(char *const argv[], t_env *env)
{
	int		ret;
	char	*home;

	ret = 1;
	if (!argv[1])
	{
		if (!find_env_variable_cb(env, "HOME", &home))
			{
				print_error("minishell: cd: HOME not set\n");
				return (1);
			}
		ret = chdir(home);
	}
	else if (!is_dir(argv[1]))
	{
		print_error2("Not a directory", argv[1]);
		exit(1);
	}
	else
		ret = chdir(argv[1]);
	if (ret)
		print_error("ERROR CD\n");
	return ((ret == 0) ? 0 : 1);
}

int			env_biultin(char *const argv[], t_env *env)
{
	(void)argv, (void)env;
	print_env(env);
	return (0);
}

int			export_biultin(char *const argv[], t_env *env)
{
	int i;
	int ret;

	i = 1;
	ret = 1;
	while (ret &&  argv[i])
	{
		ret = add_env_variable_expr(env, argv[i], ft_strlen(argv[i]));
		if (!ret)
			print_error("minishell: bad assignment\n");
		i++;
	}
	return (!ret);
}

int			unset_biultin(char *const argv[], t_env *env)
{
	int i;

	i = 1;
	while (argv[i])
	{
		remove_env_variable(env, argv[i], ft_strlen(argv[i]));
		i++;
	}
	return (0);
}

int			pwd_biultin(char *const argv[], t_env *env)
{
	(void)argv, (void)env;
	char	path[500];
	if (getcwd(path, 500))
		write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	return (0);
}

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
		//ft_printf(">>[%s] in: %d  out: %d\n", prog->arguments[0], prog->fd[0], prog->fd[1]);
		if (prog->fd[0] == -1)
		{
			ft_printf("minishell: %s: No such file or directory\n", prog->redirect_filename[0]); //FIXME to stderr
			return (free_pipes(pipes, 1));
		}
		exec_redirected(exec_func, exec_path, prog->arguments, fds, env);
		if (exec_path)
			free(exec_path);
		i++;
	}
	return (free_pipes(pipes, 0));
}

