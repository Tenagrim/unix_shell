/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 18:35:33 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 19:09:08 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <libft.h>

int	replace_env_variable(t_env *env, char *key, char *replace)
{
	t_var	*p;
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (!res && i < env->var_count)
	{
		p = &(env->var[i]);
		if (!ft_strcmp(key, p->key))
		{
			free(p->value);
			p->value = replace;
			p->value_len = ft_strlen(replace);
			res = 1;
		}
		i++;
	}
	return (res);
}
