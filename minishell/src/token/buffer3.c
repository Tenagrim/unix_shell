/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:23:35 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 13:32:02 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

void	tkz_buffer_skip_whitespaces(t_tkz_buf *buf)
{
	char c;

	while ((c = tkz_buffer_view_char(buf, 0)) && !tkz_is_endcommand(c) &&
			tkz_is_wp(c))
		tkz_buffer_increment(buf, 1);
}

int		tkz_buffer_is_endcommand(t_tkz_buf *buf)
{
	char c;

	while ((c = tkz_buffer_view_char(buf, 0)) && !tkz_is_endcommand(c) &&
			tkz_is_wp(c))
		tkz_buffer_increment(buf, 1);
	return (tkz_is_endcommand(c));
}

void	tkz_buffer_full_skip_endcommand(t_tkz_buf *buf)
{
	char c;

	while ((c = tkz_buffer_view_char(buf, 0)) && !tkz_is_endcommand(c))
		tkz_buffer_increment(buf, 1);
	tkz_buffer_increment(buf, 1);
}

int		tkz_is_command_buffered(t_tkz *tkz)
{
	int		prev_start;
	int		prev_len;
	char	c;
	int		result;

	prev_start = tkz->buf.start;
	prev_len = tkz->buf.len;
	while ((c = tkz_buffer_view_char(&tkz->buf, 0)) && !tkz_is_endcommand(c))
		tkz_buffer_increment(&tkz->buf, 1);
	result = tkz_is_endcommand(c);
	tkz->buf.start = prev_start;
	tkz->buf.len = prev_len;
	return (tkz->buf.fd >= 0 ? result : 1);
}
