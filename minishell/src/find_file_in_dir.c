/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file_in_dir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 12:29:28 by gshona            #+#    #+#             */
/*   Updated: 2020/12/27 13:11:57 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <dirent.h>

/*
** return:	-1 - error (no such directory)
** 			0  - not found
** 			1  - found
*/

int		find_file_in_dir(char *dir_name, char *file)
{
	DIR				*dir;
	int				len;
	struct	dirent	*opend_dir;

	dir = opendir(dir_name);
	if (!dir)
		return (-1);
	len = ft_strlen(file);
	while ((opend_dir = readdir(dir)) != NULL)
		if (opend_dir->d_namlen == len && !(ft_strcmp(opend_dir->d_name, file)))
		{
			closedir(dir);
			return (1);
		}
	closedir(dir);
	return (0);
}
