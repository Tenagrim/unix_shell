/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpful.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:30:40 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 16:57:12 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdlib.h>

int		copy_string(char *str, char **out, int *out_len_canbenull)
{
	int		success;
	int		len;
	int		i;

	success = 0;
	if (!str)
		return (success);
	len = 0;
	while (str[len])
		len += 1;
	*out = malloc(len + 1);
	if (!*out)
		return (success);
	i = 0;
	while (i < len)
	{
		(*out)[i] = str[i];
		i += 1;
	}
	(*out)[i] = 0;
	if (out_len_canbenull)
		*out_len_canbenull = len;
	success = 1;
	return (success);
}

int		string_eq(char *l, char *r)
{
	while (*l && *l == *r)
	{
		l += 1;
		r += 1;
	}
	return (*l == *r);
}

void	env_memcpy(void *l, void *r, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)l)[i] = ((unsigned char *)r)[i];
		i += 1;
	}
}
