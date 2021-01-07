/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:11:07 by gshona            #+#    #+#             */
/*   Updated: 2021/01/07 17:55:09 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	inc_shlvl(t_env *env)
{
	int		shlvl;
	char	*tmp;

	if (!find_env_variable_cb_static(env, "SHLVL", &tmp))
	{
		add_env_variable(env, "SHLVL", "1");
		return (1);
	}
	shlvl = ft_atoi(tmp) + 1;
	tmp = ft_itoa(shlvl);
	add_env_variable(env, "SHLVL", tmp);
	free(tmp);
	return (1);
}
