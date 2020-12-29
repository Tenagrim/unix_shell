/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:23:09 by gshona            #+#    #+#             */
/*   Updated: 2020/12/29 19:24:42 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>

int	is_dir(char *name)
{
	struct	stat buff;
	int		ret;

	ret = stat(name, &buff);
	return (buff.st_mode & S_IFDIR);
}

