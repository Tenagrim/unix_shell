/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:36:52 by gshona            #+#    #+#             */
/*   Updated: 2021/01/06 20:07:49 by tenagrim         ###   ########.fr       */
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

int			ft_atoi_bust(char *str)
{
	int	min;
	char	*tmp;
	int	res;

	tmp = ft_strtrim(str, " \v\t\f\r\n");
	str = tmp;
	min = (*str == '-');
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	res = ft_atoi(str);
	free(tmp);
	res = (min) ? -res : res;
	return (res);
}

int			exit_biultin(char *const argv[], t_env *env)
{
	int	ex_code;
	char	*str;

	ex_code = 0;
	if (argv[1])
	{
		str = argv[1];
		if (!is_right_digit(str))
		{
			ex_code = 2;
			print_error3("exit", str,
					"numeric argument required");
		}
		else
			ex_code = ft_atoi_bust(str);
	}
	free_env(&env);
	exit(ex_code);
}
