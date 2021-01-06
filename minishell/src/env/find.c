/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:44:11 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 16:48:05 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int		find_env_variable(t_env *env, char *key)
{
	int		i;
	t_var	*var;
	int		success;

	success = 0;
	i = 0;
	while (i < env->var_count)
	{
		var = &env->var[i];
		if (string_eq(key, var->key))
			break ;
		i += 1;
	}
	return (i < env->var_count ? i : -1);
}

int		find_env_variable_cb(t_env *env, char *key, char **value_canbenull)
{
	int		i;
	t_var	*var;
	int		success;

	success = 0;
	i = find_env_variable(env, key);
	if (i >= 0)
	{
		var = &env->var[i];
		if (value_canbenull)
		{
			if (copy_string(var->value, value_canbenull, 0))
				success = 1;
		}
		else
			success = 1;
	}
	return (success);
}

int		find_env_variable_cb_static(t_env *env, char *key,
	char **value_canbenull)
{
	int		i;
	t_var	*var;
	int		success;

	success = 0;
	i = find_env_variable(env, key);
	if (i >= 0)
	{
		var = &env->var[i];
		if (value_canbenull)
		{
			*value_canbenull = var->value;
			success = 1;
		}
		else
			success = 1;
	}
	return (success);
}
