/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:17:57 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 13:21:52 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		get_last_code(void *data, int *exit_code)
{
	t_env *env;

	env = (t_env*)data;
	*exit_code = env->last_code;
	return (0);
}
