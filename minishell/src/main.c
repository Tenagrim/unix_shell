/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:22:18 by gshona            #+#    #+#             */
/*   Updated: 2020/12/29 16:32:19 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <printf.h> //FIXME

int		find_by_path(char *name)
{
	struct	stat buff;
	int		ret;

	ret = stat(name, &buff);
	printf("{{%d}} IFDIR: %d\n", buff.st_mode, buff.st_mode & S_IFDIR);
	return (( ret == 0) ? 1 : 0);
}

int		main(int ac, char **av, char **env)
{
	t_super *super;
	int		err;

	//super = make_super_repl(env);
	//ft_printf("%s\n", av[0]);
 	signal(2, signal_handler);
	signal(3, signal_handler);
	err = 1;
	while (err == 1)
	{
		write_prompt();
		super = init_super();
		err =  make_super(super);

		//print_super(super);
		exec_commands(super, env);
		//free_super(&super);
		//ft_printf("%d -------\n",err);
	}
}
