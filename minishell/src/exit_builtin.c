/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:36:52 by gshona            #+#    #+#             */
/*   Updated: 2021/01/06 14:43:20 by tenagrim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			is_right_digit(char *str1)
{
	int	ret;
	char	*str;
	char	*tmp;

	ret = 0;
	str = ft_strtrim(str1, " \v\t\f\r\n");
	tmp = str;
	if (*str == '-' || *str == '+')
	{
		ret = -1;
		str++;
	}
	while (*str)
	{
		ret = 1;
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	free(tmp);
	return (!(ret == -1));
}

int			exit_biultin(char *const argv[], t_env *env)
{
	int	ex_code;

	(void)argv;
	ex_code = 0;
	if (argv[1])
	{
		if (!is_right_digit(argv[1]))
		{
			ex_code = 2;
			print_error3("exit", argv[1],
					"numeric argument required");
		}
		else
			ex_code = ft_atoi(argv[1]);
	}
	free_env(&env);
	exit(ex_code);
}
