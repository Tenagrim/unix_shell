/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:22:18 by gshona            #+#    #+#             */
/*   Updated: 2020/12/27 15:43:34 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define C_LFT_RDR	(1 << 0)
#define C_RT_RDR	(1 << 1)
#define C_RTT_RDR	(1 << 2)

typedef struct
{
	unsigned int	flags;
	char			filenames[2];
	char			**argv;
	char			**env;
	int				fds[2];
}					t_cmd_args;

char	**argv0_gen(char *command, char *av_1)
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
/*
void	pipe_head(int *fds, char **av)
{
		close(fds[0]);
        dup2(fds[1], 1);
		ret = execve(av[0], av, env);
		ft_printf("execve returned: %d\n", ret);
		exit(0);
}

void	red_in(int *fds)
{
		close(fds[1]);
        dup2(fds[0], 0);
}
*/



char	*get_path_with_env(char **env, char *name)
{
	return(find_path(get_env_value(env, "PATH"), name));
}

int		main(int ac, char **av, char **env)
{
	int fd1;
	int	fd2;
	t_cmd_args args;

	int	fds[2];

	//fd1 = open("file", O_WRONLY | O_CREAT, 0644);
	fd1 = open("file", O_RDONLY);
	fd2 = open("file_out", O_WRONLY | O_CREAT, 0644);


	pipe(fds);
	exec_redirected(argv1_gen(get_path_with_env(env, "ls"), "."), 0, fds[1], env);
	exec_redirected(argv1_gen(get_path_with_env(env, "grep"), "l"), fds[0], 1, env);
	//ft_printf("[%d]\t[%d]\n", fd1, fd2);
	//exec_redirected(argv1_gen(get_path_with_env(env, "cat"), "-e"), fd1, fd2, env);
	

	ft_printf("END\n");
}
