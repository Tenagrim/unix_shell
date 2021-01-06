/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:28:10 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 17:01:21 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <unistd.h>
#include <stdlib.h>

void	init_env_var(t_var *var)
{
	var->key_len = 0;
	var->key = 0;
	var->value_len = 0;
	var->value = 0;
}

t_env	*init_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env)
	{
		env->last_code = 0;
		env->var_cap = 16;
		env->var_count = 0;
		env->var = malloc(sizeof(t_var) * env->var_cap);
		if (!env->var)
			free_env(&env);
	}
	return (env);
}
