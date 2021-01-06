/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:46:02 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 16:55:35 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdlib.h>
#include <unistd.h>

int		local_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i += 1;
	return (i);
}

void	print_env(t_env *env)
{
	int		i;
	t_var	*var;
	char	*expr;

	i = 0;
	while (i < env->var_count)
	{
		var = &env->var[i];
		expr = gen_var_expr(var);
		if (expr)
		{
			write(1, expr, local_strlen(expr));
			write(1, "\n", 1);
			free(expr);
		}
		i += 1;
	}
}
