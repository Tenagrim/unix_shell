/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:22:18 by gshona            #+#    #+#             */
/*   Updated: 2020/12/28 22:12:41 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <printf.h>




int		find_by_path(char *name)
{
	struct	stat buff;
	int		ret;

	ret = stat(name, &buff);
	printf("{{%d}} IFDIR: %d\n", buff.st_mode, buff.st_mode & S_IFDIR);
	return (( ret == 0) ? 1 : 0);
}


void	write_prompt(char **env)
{
	char	*prompt;

	//prompt = get_env_value(env, "PS1");
	//printf("")
	//if (*prompt == 0)
		prompt = "prompt> ";
	write(2, prompt, ft_strlen(prompt));
}

void	kill_child(int sig)
{
	//kill(pid, 2);
	printf("{%d}\n", sig);
	write(2,"\n",1);
}
void	kill_quit(int sig)
{
	//kill(pid, 3);
	printf("{%d}\n", sig);
	write(2,"Quit: 3\n",8);
}

void	kill_quit_2(int sig)
{
	//kill(pid, 3);
	printf(">>>{%d}\n", sig);
	write(2,"Quit: 3\n",8);
}

int		main(int ac, char **av, char **env)
{
	t_super *super;
	//super = make_super_repl(env);
	//ft_printf("%s\n", av[0]);
 	signal(2, kill_child);
	signal(3, kill_quit);
	signal(3, kill_quit_2);
	while (1)
	{
		write_prompt(env);
		super = init_super();
		make_super(super);

		//replace_execs(super, env);
	//print_super(super);
		exec_commands(super, env);
		free_super(&super);
	//ft_printf("[%d]\t[%d]\n", fd1, fd2);
	//exec_redirected(argv1_gen(get_path_with_env(env, "cat"), "-e"), fd1, fd2, env);

	//char *name = NULL;

	//ft_printf("[%d]  [%s]\n", get_command_ex(NULL, env, av[1], &name), name);

	//ft_printf("END\n");
	}
	//signal(2, sigint_old);
}
