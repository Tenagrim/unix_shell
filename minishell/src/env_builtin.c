/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:34:31 by gshona            #+#    #+#             */
/*   Updated: 2021/01/06 14:32:48 by tenagrim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			env_biultin(char *const argv[], t_env *env)
{
	(void)argv;
	(void)env;
	print_env(env);
	return (0);
}
