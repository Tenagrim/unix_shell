/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:31:55 by gshona            #+#    #+#             */
/*   Updated: 2021/01/06 18:16:23 by tenagrim         ###   ########.fr       */
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
	int	len;

	len = ft_strlen(str);
	i = 0;
	if ((len == 1 && *str == '=') || len == 0)
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!is_identifier_l(str[i], i))
			return (0);
		i++;
	}
	return (1);
}

static void		err_bad_assignment(char *str)
{
	write(2, "minishell: export: `", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
}

int			export_biultin(char *const argv[], t_env *env)
{
	int		i;
	int		ret;
	int		last;

	i = 0;
	ret = 1;
	last = 0;
	while (ret && argv[++i])
	{
		if (!check_identifier(argv[i]))
		{
			err_bad_assignment(argv[i]);
			last = 1;
			continue ;
		}
		ret = add_env_variable_expr(env, argv[i]);
		last = !ret;
		if (!ret)
			err_bad_assignment(argv[i]);
	}
	return (last);
}
