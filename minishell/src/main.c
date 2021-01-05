/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:22:18 by gshona            #+#    #+#             */
/*   Updated: 2021/01/05 20:58:41 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <printf.h> //FIXME

/*
int		find_by_path(char *name)
{
	struct	stat buff;
	int		ret;

	ret = stat(name, &buff);
	printf("{{%d}} IFDIR: %d\n", buff.st_mode, buff.st_mode & S_IFDIR);
	return (( ret == 0) ? 1 : 0);
}
*/

int		add_env_pwd(t_env *env)
{
	char	*pwd;

	if (find_env_variable(env, "PWD") == -1)
	{
		pwd = pwd_function();
		pwd = (pwd) ? pwd : ft_strdup("very very long path");
		add_env_variable(env, "PWD", pwd);
		return (1);
	}
	return (0);
}

t_env		*make_env(char **env_n)
{
	t_env	*env;

	env = init_env();
	merge_env_native(env, env_n);
	inc_shlvl(env);
	return (env);
}

int		main(int ac, char **av, char **env)
{
	t_super		*super;
	t_env		*env_t;
	int			err;

 	signal(2, signal_handler);
	signal(3, signal_handler);
	err = 1;
	env_t = make_env(env);
	super = init_super();
	super->tkz->env_get = find_env_variable_cb_static;
	super->tkz->last_exit_code = get_last_code;
	super->tkz->data = env_t;
	if (ac == 3 && !ft_strcmp(av[1], "-c"))
	{
		int		len = strlen(av[2]);
		memcpy(super->tkz->buf.mem, av[2], len);
		super->tkz->buf.mem[len++] = '\n';
		super->tkz->buf.start = 0;
		super->tkz->buf.len = len;
		super->tkz->buf.fd = -1;
	}

	while (1)
	{
		if (!tkz_is_command_buffered(super->tkz))
			write_prompt();
		err =  make_super(super);
		// print_super(super);
		// tkz_print(super->tkz);
		// printf ("err: %d\n", err);
		if (err == TKZ_ERROR_UNISTD_READ_EOF || err == TKZ_ERROR_INVALID_FD)
			break ;
		if (tkz_check_flags(super->tkz, TKZ_FLAG_UNEXPECTED_EOF))
			write(2, "\n", 1);
			//printf("\n");
		if (is_super_error(err))
			print_error1((char*)(super_error_str(err)));
			//printf("minishell: %s\n", super_error_str(err));
		else
			exec_commands(super, env_t);
		if (tkz_check_flags(super->tkz, TKZ_FLAG_QUOTE_NL_END))
		{
			env_t->last_code = 2;
			if (ac == 3)
				break ;
		}
		//ft_printf("%d -------\n",err);
	}

	if (ac == 1)
		write(2, "exit\n", 5);

	int last_code = env_t->last_code;
	free_super(&super);
	free_env(&env_t);

	return (last_code);
}
