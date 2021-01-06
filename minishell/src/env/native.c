/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   native.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:45:25 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 17:01:38 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdlib.h>

char	*gen_var_expr(t_var *var)
{
	char	*expr;

	expr = malloc(var->key_len + var->value_len + 2);
	if (expr)
	{
		env_memcpy(expr, var->key, var->key_len);
		expr[var->key_len] = '=';
		env_memcpy(expr + var->key_len + 1, var->value, var->value_len);
		expr[var->key_len + 1 + var->value_len] = 0;
	}
	return (expr);
}

char	**gen_native_env(t_env *env)
{
	char	**native;
	t_var	*var;
	int		i;

	native = malloc(sizeof(char *) * (env->var_count + 1));
	if (!native)
		return (0);
	i = 0;
	while (i < env->var_count)
	{
		var = &env->var[i];
		native[i] = gen_var_expr(var);
		if (!native[i])
			break ;
		i += 1;
	}
	native[i] = 0;
	return (native);
}

int		merge_env_native(t_env *env, char **native)
{
	while (*native)
	{
		if (!add_env_variable_expr(env, *native))
			break ;
		native += 1;
	}
	return (!*native);
}
