/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpful.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:42:36 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 13:32:53 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

void	tkz_memcpy(void *l, void *r, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		((unsigned char *)l)[i] = ((unsigned char *)r)[i];
		i += 1;
	}
}

int		tkz_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i += 1;
	return (i);
}

void	tkz_reverse_str(char *begin, int len)
{
	char	*end;
	char	temp;

	end = begin + len - 1;
	while (begin < end)
	{
		temp = *begin;
		*begin = *end;
		*end = temp;
		begin += 1;
		end -= 1;
	}
}

int		tkz_draw_int(char *out, int num)
{
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	if (num < 0)
		sign = -1;
	if (sign < 0)
		out[i++] = '-';
	if (num == 0)
		out[i++] = '0';
	while (num != 0)
	{
		out[i++] = '0' + (sign < 0 ? -(num % 10) : num % 10);
		num /= 10;
	}
	tkz_reverse_str(out + (sign < 0), i - (sign < 0));
	return (i);
}

int		tkz_strchr(char c, const char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i += 1;
	return (str[i] == c);
}
