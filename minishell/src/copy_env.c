/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:34:54 by gshona            #+#    #+#             */
/*   Updated: 2021/01/06 14:35:38 by tenagrim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**copy_env(char **env)
{
	char	**res;
	int		count;
	int		i;

	count = 0;
	while (env[count])
		count++;
	ft_printf(">>%d\n", count);
	res = (char**)malloc(sizeof(char*) * (count));
	res[count - 1] = NULL;
	i = -1;
	while (i++ < count - 2)
		res[i] = ft_strdup(env[i]);
	return (res);
}
