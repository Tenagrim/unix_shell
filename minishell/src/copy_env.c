/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:34:54 by gshona            #+#    #+#             */
/*   Updated: 2021/01/07 17:35:46 by jsandsla         ###   ########.fr       */
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
