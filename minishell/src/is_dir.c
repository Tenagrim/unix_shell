/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:23:09 by gshona            #+#    #+#             */
/*   Updated: 2021/01/06 19:18:27 by tenagrim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>

int	is_dir(char *name)
{
	struct stat	buff;
	int		ret;

	ret = stat(name, &buff);
	return ((!ret) ? (int)(buff.st_mode & S_IFDIR) : -1);
}
