/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:22:18 by gshona            #+#    #+#             */
/*   Updated: 2020/12/27 13:32:37 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_loop()
{
	

}


int		exec_command(char **av, char **env)
{
	int	pid;
	int	status;
	int	ret;

	ret = 0;
	pid = fork();
	if (!pid)
	{
		//ft_printf(">>> %s\n", av[0]);
		ret = execve(av[0], av, env);
		ft_printf("execve returned: %d\n", ret);
		exit(ret);
	}
	else
	{
		//ft_printf("start wait\n");
		wait(&status);
		//ft_printf("end wait\n");
	}
	return (ret);
}

char	**argv_gen(char *command, char *av_1)
{
	char **res;
	res = malloc(sizeof(char*) * 3);
	res[2] = NULL;
	res[1] = NULL;
	//res[1] = ft_strdup(av_1);
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
		int file = open("testfile_3", O_RDWR | O_CREAT, 0644);
		dup2(file, fds[1]);
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



int		main(int ac, char **av, char **env)
{
	int	fds[2];

	//exec_piped_commands(argv_gen("/bin/cat", "testfile"), argv_gen("/usr/bin/grep", "1111"), env);
	//pipe(fds);
	//red_out(fds);
	//exec_command(argv_gen("/bin/echo", "hello world\n"), env, 0, fds[1], fds);
	//red_in(fds);
	//exec_command(argv_gen("/bin/cat", "-e"), env, fds[0], 1, fds);


	//int file1 = open("testfile_3", O_RDWR | O_CREAT, 0644);
	//ft_printf("[%d]\n", find_file_in_dir("/Users/gshona/.brew/bin/", "ls"));
	//ft_printf("path: |%s|\n", find_path(get_env_value(env, "PATH"), "ls"));
	
	//ft_printf("|%s|\n", get_full_path("/usr/bin", "cat"));
	
	char	*prog;
	char	*path = get_env_value(env, "PATH");
	prog = find_path(path, av[1]);

	ft_printf("[%s]\n", prog);

	exec_command(argv_gen(prog, NULL), env);	

	//ft_printf("END\n");
}
