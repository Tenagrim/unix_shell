/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:11:07 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 19:25:41 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	inc_shlvl(t_env *env)
{
	int		shlvl;
	char	*tmp;

	if (!find_env_variable_cb_static(env, "SHLVL", &tmp))
		return (0);
	shlvl = ft_atoi(tmp) + 1;
	tmp = ft_itoa(shlvl);
	replace_env_variable(env, "SHLVL", tmp);
	return (1);
}
