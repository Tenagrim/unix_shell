/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:23:09 by gshona            #+#    #+#             */
/*   Updated: 2021/01/07 17:37:14 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>

int	is_dir(char *name)
{
	struct stat	buff;
	int			ret;

	ret = stat(name, &buff);
	return ((!ret) ? (int)(buff.st_mode & S_IFDIR) : -1);
}
