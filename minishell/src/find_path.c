/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 13:18:33 by gshona            #+#    #+#             */
/*   Updated: 2021/01/07 17:44:58 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

static char	*get_full_path(char *dir_name, char *name)
{
	int		len1;
	int		len2;
	char	*res;
	int		i;

	len1 = ft_strlen(dir_name);
	len2 = ft_strlen(name);
	if (!(res = (char*)malloc(sizeof(char) * (len1 + len2 + 2))))
		return (NULL);
	res[len1 + len2 + 1] = 0;
	i = -1;
	while (i++ < len1)
		res[i] = dir_name[i];
	res[len1++] = '/';
	i = -1;
	while (i++ < len2)
		res[len1 + i] = name[i];
	return (res);
}

char		*find_path(char *path, char *name)
{
	char	*dir_name;
	char	*sep;
	char	*res;

	res = NULL;
	while (!res && (sep = ft_strchr(path, ':')))
	{
		if (!(dir_name = ft_substr(path, 0, sep - path)))
			return (NULL);
		if (find_file_in_dir(dir_name, name) == 1)
			res = get_full_path(dir_name, name);
		free(dir_name);
		path = sep + 1;
	}
	if (!res && *path && find_file_in_dir(path, name) == 1)
		res = get_full_path(path, name);
	return (res);
}
