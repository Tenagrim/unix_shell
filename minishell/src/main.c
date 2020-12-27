/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:22:18 by gshona            #+#    #+#             */
/*   Updated: 2020/12/27 16:57:24 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



typedef struct
{
	unsigned int	flags;
	char			filenames[2];
	char			**argv;
	char			**env;
	int				fds[2];
}					t_cmd_args;

char	**argv0_gen(char *command)
{
	char **res;
	res = malloc(sizeof(char*) * 3);
	res[2] = NULL;
	res[1] = NULL;
	//res[1] = ft_strdup(av_1);
	res[0] = ft_strdup(command);
	return (res);
}

char	**argv1_gen(char *command, char *av_1)
{
	char **res;
	res = malloc(sizeof(char*) * 3);
	res[2] = NULL;
	res[1] = NULL;
	res[1] = ft_strdup(av_1);
	res[0] = ft_strdup(command);
	return (res);
}

/*
int		exec_piped_commands(char **av1, char **av2, char **env)
{
	int	pid;
	int	fds[2];
	int	ret;

	pipe(fds);
	pid = fork();
	if (pid == -1)
	{
		ft_printf("error in fork\n");
		return (1);
	}
	else if (pid == 0)
	{
		
		close(fds[1]);
        dup2(fds[0], 0);
		ret = execve(av2[0], av2, env);
		ft_printf("execve returned: %d\n", ret);
		exit(ret);
	}
	else
	{
		close(fds[0]);
        dup2(fds[1], 1);
		ret = execve(av1[0], av1, env);
		ft_printf("execve returned: %d\n", ret);
		exit(ret);
	}
	return (0);
}
*/

char	*get_path_with_env(char **env, char *name)
{
	return(find_path(get_env_value(env, "PATH"), name));
}

static int	**make_pipes(void)
{
	int	**res;

	res = (int**)malloc(sizeof(int*) * 2);
	res[0] = (int*)malloc(sizeof(int) * 2);
	res[1] = (int*)malloc(sizeof(int) * 2);
	return (res);
}

int		exec_commands(t_super *progs)
{
	int			i;
	int			**pipes;
	int			*cur_pipe;
	t_program	*prog;

	pipes = make_pipes();
	cur_pipe = pipes[0];   //FIXME
	i = 0;
	while (i < progs->count)
	{	
		prog = progs->programs + i;
		if (prog->flags & C_PIPE)
		{
			pipe(cur_pipe);
			prog->fd[1] = cur_pipe[1];
			progs->programs[i + 1].fd[0] = cur_pipe[0];
		}
		if (prog->flags & C_LFT_RDR)
			prog->fd[0] = open(prog->redirect_filename[0], O_RDONLY);
		if (prog->flags & C_RT_RDR)
			prog->fd[1] = open(prog->redirect_filename[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (prog->flags & C_RTT_RDR)
			prog->fd[1] = open(prog->redirect_filename[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		ft_printf(">>[%s]\n", prog->arguments[0]);
		exec_redirected(prog->arguments, prog->fd[0], prog->fd[1], prog->env);
		i++;
	}
	return (0);
}

t_super	*make_super_repl(char **env)
{
	t_super *res;

	res = malloc(sizeof(t_super));
	res->programs = malloc(sizeof(t_program) * 2);
	res->count = 2;
	res->cap = 2;
	res->programs[0].arguments = argv0_gen("/bin/ls");
	res->programs[1].arguments = argv1_gen("/bin/cat", "-e");
	
	res->programs[0].fd[0] = 0;
	res->programs[0].fd[1] = 1;
	res->programs[1].fd[0] = 0;
	res->programs[1].fd[1] = 1;
	
	res->programs[0].env = env;
	res->programs[1].env = env;
	
	res->programs[0].flags = 0;
	res->programs[1].flags = C_LFT_RDR;
	
	res->programs[0].redirect_filename[1] = "qwe";
	res->programs[1].redirect_filename[0] = "qwe";
	return (res);
}




int		main(int ac, char **av, char **env)
{
	t_super *super;

	super = make_super_repl(env);

	exec_commands(super);
	//ft_printf("[%d]\t[%d]\n", fd1, fd2);
	//exec_redirected(argv1_gen(get_path_with_env(env, "cat"), "-e"), fd1, fd2, env);
	

	ft_printf("END\n");
}
