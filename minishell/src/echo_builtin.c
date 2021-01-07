/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:36:10 by gshona            #+#    #+#             */
/*   Updated: 2021/01/07 17:37:44 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_flags(char *const argv[], char ***first_arg)
{
	int	res;
	int	i;
	int	j;

	res = 0;
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-' && argv[i][1])
		{
			j = 0;
			while (argv[i][++j])
				if (argv[i][j] == 'n')
					res = 1;
		}
		else
			break ;
		i++;
	}
	*first_arg = (char **)(argv) + i;
	return (res);
}

int	echo_biultin(char *const argv[], t_env *env)
{
	char		min_n;
	int			i;
	char		**first_arg;
	char		f;

	(void)env;
	min_n = skip_flags(argv, &first_arg);
	i = 0;
	f = 0;
	while (first_arg[i])
	{
		f = 1;
		write(1, first_arg[i], ft_strlen(first_arg[i]));
		if (first_arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if ((!min_n && f) || !argv[1])
		write(1, "\n", 1);
	return (0);
}
