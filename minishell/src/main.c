/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:22:18 by gshona            #+#    #+#             */
/*   Updated: 2021/01/07 13:33:43 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <printf.h> //FIXME

t_env	*make_env(char **env_n)
{
	t_env	*env;

	env = init_env();
	merge_env_native(env, env_n);
	inc_shlvl(env);
	return (env);
}

int		should_prequit(int err)
{
	return (err == TKZ_ERROR_UNISTD_READ_EOF || err == TKZ_ERROR_INVALID_FD);
}

int		should_postquit(t_super *super, t_env *env, int err)
{
	int		should;

	should = 0;
	if (tkz_check_flags(super->tkz, TKZ_FLAG_QUOTE_NL_END) ||
		err == SUP_ERROR_INVALID_SYNTAX || err == SUP_ERROR_NO_ARGUMENTS ||
		err == SUP_ERROR_MISSING_REDIRECTION_FILE)
	{
		env->last_code = 2;
	}
	return (should);
}

int		main_loop(t_super *super, t_env *env)
{
	int		error;

	while (1)
	{
		if (!tkz_is_command_buffered(super->tkz))
			write_prompt();
		error = make_super(super);
		// print_super(super);
		// tkz_print(super->tkz);
		// printf ("error: %d\n", error);
		if (should_prequit(error))
			break ;
		if (tkz_check_flags(super->tkz, TKZ_FLAG_UNEXPECTED_EOF))
			write(2, "\n", 1);
		if (is_super_error(error))
			print_error1((char*)(super_error_str(error)));
		else
			if (exec_commands(super, env))
				break ;
		if (should_postquit(super, env, error))
			break ;
	}
	return (env->last_code);
}

int		main(int ac, char **av, char **env)
{
	t_super		*super;
	t_env		*env_t;
	int			last_code;

	(void)ac;
	(void)av;
	signal(2, signal_handler);
	signal(3, signal_handler);
	env_t = make_env(env);
	super = init_super();
	super->tkz->env_get = (t_tkz_env_get)find_env_variable_cb_static;
	super->tkz->last_exit_code = (t_tkz_last_exit_code)get_last_code;
	super->tkz->data = env_t;
	last_code = main_loop(super, env_t);
	write(2, "exit\n", 5);
	free_super(&super);
	free_env(&env_t);
	return (last_code);
}
