/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:46:01 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 12:59:43 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int		tkz_buffer_expand(t_tkz_buf *buf, int at_least);
int		tkz_write_buffer_str(t_tkz_buf *buf, const char *str, int len);
int		tkz_buffer_read_command(t_tkz *tkz, t_tkz_buf *buf)
int		tkz_read_buffer(t_tkz_buf *buf);

int		tkz_buffer_expand(t_tkz_buf *buf, int at_least)
{
	int		new_cap;
	void	*new_mem;

	new_cap = buf->cap * 2;
	if (new_cap < at_least)
		new_cap = (at_least + 63) & -64;
	if (new_cap <= 0)
		new_cap = 16;
	new_mem = malloc(new_cap);
	if (new_mem)
	{
		if (buf->mem && buf->len > 0)
		{
			tkz_memcpy(new_mem, buf->mem + buf->start, buf->len);
			free(buf->mem);
		}
		buf->mem = new_mem;
		buf->cap = new_cap;
		buf->start = 0;
	}
	return (!!new_mem ? TKZ_SUCCESS : TKZ_ERROR_MALLOC_NULL_RETURN);
}

int		tkz_write_buffer_str(t_tkz_buf *buf, const char *str, int len)
{
	int		error;

	error = TKZ_SUCCESS;
	if (buf->start + buf->len + len > buf->cap)
		error = tkz_buffer_expand(buf, buf->start + buf->len + len);
	if (!tkz_is_error(error))
	{
		tkz_memcpy(buf->mem + buf->start + buf->len, (void *)str, len);
		buf->len += len;
	}
	return (error);
}

int		tkz_buffer_read_command(t_tkz *tkz, t_tkz_buf *buf)
{
	int		error;

	error = TKZ_SUCCESS;
	while (!tkz_is_error(error) && !tkz_is_buffer_closed(buf))
	{
		error = tkz_read_buffer(buf);
		if (error == TKZ_ERROR_UNISTD_READ_EOF && buf->len > 0)
		{
			tkz->flags |= TKZ_FLAG_UNEXPECTED_EOF;
			error = TKZ_SUCCESS;
			break ;
		}
		if (buf->len > 0 && tkz_is_wp(tkz_buffer_view_char(buf, 0)))
			tkz->flags |= TKZ_FLAG_WS_AT_START;
	}
	if (!tkz_is_error(error))
		tkz_buffer_skip_whitespaces(buf);
	return (error);
}

int		tkz_read_buffer(t_tkz_buf *buf)
{
	int		ret;
	int		error;
	char	bufmem[64];

	if (buf->len > 0 && buf->start > 0)
		tkz_memcpy(buf->mem, buf->mem + buf->start, buf->len);
	buf->start = 0;
	error = TKZ_SUCCESS;
	if (buf->len < buf->cap && buf->fd >= 0)
	{
		while (!tkz_is_error(error) && !tkz_is_buffer_closed(buf))
		{
			ret = read(buf->fd, bufmem, sizeof(bufmem));
			if (ret < 0)
				return (TKZ_ERROR_UNISTD_READ_NEGATIVE_RETURN);
			if (ret == 0)
				return (TKZ_ERROR_UNISTD_READ_EOF);
			error = tkz_write_buffer_str(buf, bufmem, ret);
		}
	}
	return (buf->fd >= 0 ? error : TKZ_ERROR_INVALID_FD);
}
