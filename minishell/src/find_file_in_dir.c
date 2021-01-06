/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file_in_dir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 12:29:28 by gshona            #+#    #+#             */
/*   Updated: 2021/01/06 19:10:33 by tenagrim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <dirent.h>

int		find_file_in_dir(char *dir_name, char *file)
{
	DIR				*dir;
	struct dirent			*opend_dir;

	dir = opendir(dir_name);
	if (!dir)
		return (-1);
	while ((opend_dir = readdir(dir)) != NULL)
		if (!(ft_strcmp(opend_dir->d_name, file)))
		{
			closedir(dir);
			return (1);
		}
	closedir(dir);
	return (0);
}
