/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:17:57 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 13:25:03 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		get_last_code(void *data, int *exit_code)
{
	t_env *env;

	env = (t_env*)data;
	*exit_code = env->last_code;
	return (1);
}
