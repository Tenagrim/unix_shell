/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:31:55 by gshona            #+#    #+#             */
/*   Updated: 2021/01/04 14:32:52 by tenagrim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		is_identifier_l(char c, int is_begin)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' ||
		(is_begin != 0 && c >= '0' && c <= '9'));
}

static int		check_identifier(char *str)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != '=')
	{
		if (!is_identifier_l(str[i], i))
			return (0);
		i++;
	}
	return (1);
}

int				export_biultin(char *const argv[], t_env *env)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	while (ret && argv[++i])
	{

		if (!check_identifier(argv[i]))
		{
			print_error3("export", argv[i], "not a valid identifier");
			continue ;
		}
		ret = add_env_variable_expr(env, argv[i]);
		if (!ret)
			print_error("minishell: bad assignment\n");
	}
	return (!ret);
}
