/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:47:57 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 12:57:15 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

void	tkz_buffer_increment(t_tkz_buf *buf, int count);
char	tkz_buffer_view_char(t_tkz_buf *buf, int offset);
char	*tkz_buffer_view(t_tkz_buf *buf, int offset);
int		tkz_is_buffer_closed(t_tkz_buf *buf);

void	tkz_buffer_increment(t_tkz_buf *buf, int count)
{
	count = count > buf->len ? buf->len : count;
	buf->start += count;
	buf->len -= count;
}

char	tkz_buffer_view_char(t_tkz_buf *buf, int offset)
{
	char	c;

	c = 0;
	if (offset < buf->len)
		c = buf->mem[buf->start + offset];
	return (c);
}

char	*tkz_buffer_view(t_tkz_buf *buf, int offset)
{
	char	*str;

	str = 0;
	if (offset < buf->len)
		str = buf->mem + buf->start + offset;
	return (str);
}

int		tkz_is_buffer_closed(t_tkz_buf *buf)
{
	int		i;

	i = buf->len - 1;
	while (i >= 0 && !tkz_is_endcommand(buf->mem[buf->start + i]))
		i -= 1;
	return (i >= 0);
}
