/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:27:08 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 17:01:14 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <unistd.h>
#include <stdlib.h>

void	free_env_var(t_var *var)
{
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	var->key = 0;
	var->value = 0;
	var->key_len = 0;
	var->value_len = 0;
}

void	free_env_vars(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->var_count)
	{
		free_env_var(&env->var[i]);
		i += 1;
	}
}

void	free_env(t_env **penv)
{
	if (*penv)
	{
		if ((*penv)->var_count)
			free_env_vars(*penv);
		if ((*penv)->var)
			free((*penv)->var);
		free(*penv);
		*penv = 0;
	}
}

void	free_env_native(char **native)
{
	void	*start;

	if (native)
	{
		start = native;
		while (*native)
		{
			free(*native);
			native += 1;
		}
		free(start);
	}
}
