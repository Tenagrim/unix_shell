/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:42:40 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 16:57:19 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdlib.h>

int		expand_env_variables_array(t_env *env)
{
	int		new_cap;
	void	*new_ptr;

	new_cap = env->var_cap * 2;
	if (new_cap <= 0)
		new_cap = 16;
	new_ptr = malloc(new_cap * sizeof(t_var));
	if (!new_ptr)
		return (0);
	if (env->var)
	{
		env_memcpy(new_ptr, env->var, env->var_count * sizeof(t_var));
		free(env->var);
	}
	env->var = new_ptr;
	env->var_cap = new_cap;
	return (1);
}

int		get_variable(t_env *env, char *key)
{
	int		i;
	int		success;

	success = 1;
	i = find_env_variable(env, key);
	if (i < 0)
	{
		if (env->var_count >= env->var_cap)
			success = expand_env_variables_array(env);
		if (success)
		{
			i = env->var_count++;
			init_env_var(&env->var[i]);
		}
	}
	return (success ? i : -1);
}

int		add_env_variable(t_env *env, char *key, char *value)
{
	int		success;
	t_var	*var;
	int		i;

	success = 1;
	if (env->var_count >= env->var_cap)
		success = expand_env_variables_array(env);
	if (!success)
		return (success);
	i = get_variable(env, key);
	success = 0;
	if (i < 0)
		return (success);
	var = &env->var[i];
	if (var->key || var->value)
		free_env_var(var);
	success = copy_string(key, &var->key, &var->key_len);
	if (success)
		success = copy_string(value, &var->value, &var->value_len);
	if (!success)
	{
		free_env_var(var);
		env->var_count -= 1;
	}
	return (success);
}

int		add_env_variable_expr(t_env *env, char *expr)
{
	int		key_len;
	char	*key;
	int		success;

	success = 0;
	key_len = 0;
	while (expr[key_len] && expr[key_len] != '=')
		key_len += 1;
	if (expr[key_len] == '=')
	{
		key = malloc(key_len + 1);
		if (key)
		{
			env_memcpy(key, expr, key_len);
			key[key_len] = 0;
			success = add_env_variable(env, key, expr + key_len + 1);
			free(key);
		}
	}
	else
		success = 1;
	return (success);
}

void	remove_env_variable(t_env *env, char *key)
{
	int		i;

	i = 0;
	while (i < env->var_count)
	{
		if (string_eq(env->var[i].key, key))
			break ;
		i += 1;
	}
	if (i < env->var_count)
	{
		free_env_var(&env->var[i]);
		env_memcpy(&env->var[i], &env->var[i + 1],
			(env->var_count - i - 1) * sizeof(t_var));
		env->var_count -= 1;
	}
}
