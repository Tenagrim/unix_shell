/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:22:18 by gshona            #+#    #+#             */
/*   Updated: 2020/12/26 12:47:40 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_loop()
{
	

}


int		exec_command(char *command, char **av, char **env)
{
	int	pid;
	int	status;
	int	ret;

	ret = 0;
	pid = fork();
	if (!pid)
	{
			ret = execve(command, av, env);
			ft_printf("execve returned: %d\n", ret);
			exit(ret);
	}
	else
		wait(&status);
	return (ret);
}

char	**argv_gen(char *command, char *av_1)
{
	char **res;
	res = malloc(sizeof(char*) * 3);
	res[2] = NULL;
	res[1] = ft_strdup(av_1);
	res[0] = ft_strdup(command);
	return (res);
}

int		exec_piped_commands(char **av1, char **av2, char **env)
{
	int	pid;
	int	fds[2];

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
		execve(av2[0], av2, env);
	}
	else
	{
		close(fds[0]);
        dup2(fds[1], 1);
		execve(av1[0], av1, env);
	}
}

int		main(int ac, char **av, char **env)
{
	int tmp[2];

	//exec_command("/bin/cat", argv_gen("/bin/cat", "src/main.c"), env);
	//exec_command("/bin/cat", av, env);
	//
	exec_piped_commands(argv_gen("/bin/cat", "src/main.c"), argv_gen("/usr/bin/wc", "-l"), env);
	ft_printf("hello\n");
}
