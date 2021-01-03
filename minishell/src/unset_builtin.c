/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:32:57 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 13:41:12 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			unset_biultin(char *const argv[], t_env *env)
{
	int i;

	i = 1;
	while (argv[i])
	{
		remove_env_variable(env, argv[i], ft_strlen(argv[i]));
		i++;
	}
	return (0);
}
