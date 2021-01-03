/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:22:18 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 13:25:12 by jsandsla         ###   ########.fr       */
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
	t_super		*super;
	t_env		*env_t;
	int			err;

 	signal(2, signal_handler);
	signal(3, signal_handler);
	err = 1;
	super = init_super();
	env_t = init_env();
	merge_env_native(env_t, env);
	super->tkz->env_get = find_env_variable_cb_static;
	super->tkz->last_exit_code = get_last_code;
	super->tkz->data = env_t;

	while (1)
	{
		if (!tkz_is_command_buffered(super->tkz))
			write_prompt();
		err =  make_super(super);
		// print_super(super);
		// tkz_print(super->tkz);
		if (err == TKZ_ERROR_UNISTD_READ_EOF)
			break ;
		if (tkz_check_flags(super->tkz, TKZ_FLAG_UNEXPECTED_EOF))
			printf("\n");
		if (is_super_error(err))
			printf("minishell: %s\n", super_error_str(err));
		else
			exec_commands(super, env_t);
		//ft_printf("%d -------\n",err);
	}

	free_super(&super);
	free_env(&env_t);
}
