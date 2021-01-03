/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:36:10 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 15:01:25 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			echo_biultin(char *const argv[], t_env *env)
{
	char	min_n;
	int		i;
	(void)env;

	i = 1;
	min_n = 0;
	if (argv[1] && !ft_strcmp("-n", argv[1]))
	{
		i++;
		min_n = 1;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!min_n)
		write(1, "\n", 1);
	return (0);
}
