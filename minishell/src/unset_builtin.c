/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:32:57 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 18:52:01 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			unset_biultin(char *const argv[], t_env *env)
{
	int i;

	i = 1;
	while (argv[i])
	{
		remove_env_variable(env, argv[i]);
		i++;
	}
	return (0);
}
