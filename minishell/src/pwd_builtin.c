/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:33:46 by gshona            #+#    #+#             */
/*   Updated: 2021/01/06 14:44:26 by tenagrim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char		*pwd_function(void)
{
	char	*path;
	int		step;
	int		size;

	step = 500;
	size = 0;
	path = NULL;
	while (size < 50000)
	{
		size += step;
		if (path)
			free(path);
		path = (char*)malloc(sizeof(char) * size);
		if (getcwd(path, size))
			break ;
	}
	return (path);
}

int			pwd_biultin(char *const argv[], t_env *env)
{
	char	*path;

	(void)argv;
	(void)env;
	if ((path = pwd_function()))
	{
		write(1, path, ft_strlen(path));
		free(path);
	}
	write(1, "\n", 1);
	return (0);
}
