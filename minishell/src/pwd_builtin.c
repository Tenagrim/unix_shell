/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:33:46 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 13:40:49 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			pwd_biultin(char *const argv[], t_env *env)
{
	(void)argv, (void)env;
	char	path[500];
	if (getcwd(path, 500))
		write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	return (0);
}
