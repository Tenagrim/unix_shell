/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprocessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:49:28 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 13:33:34 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int		tkz_subprocessor_exit_code(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	numbuf[24];
	int		numlen;
	int		exit_code;
	int		error;

	if (tkz_buffer_view_char(buf, 0) != '?')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_QUATION_MARK_SYMBOL);
	tkz_buffer_increment(buf, 1);
	numbuf[0] = '0';
	numlen = 1;
	if (tkz->last_exit_code(tkz->data, &exit_code))
		numlen = tkz_draw_int(numbuf, exit_code);
	error = tkz_write_token_str(tkn, numbuf, numlen);
	return (error);
}

t_token	tkz_subprocessor_env_get_identifier(t_tkz_buf *buf)
{
	int			iden_len;
	int			error;
	char		c;
	t_token		name;

	iden_len = 0;
	while ((c = tkz_buffer_view_char(buf, iden_len)) &&
			tkz_is_identifier(c, !iden_len))
		iden_len += 1;
	tkz_init_token(&name);
	error = tkz_write_token_str(&name, tkz_buffer_view(buf, 0), iden_len);
	tkz_buffer_increment(buf, iden_len);
	if (tkz_is_error(error))
		tkz_free_token(&name);
	return (name);
}

int		tkz_subprocessor_env(t_tkz *tkz, t_tkz_buf *buf)
{
	char		*value;
	t_tkz_buf	nbuf;
	t_token		name;
	int			error;

	error = TKZ_ERROR;
	name = tkz_subprocessor_env_get_identifier(buf);
	if (name.len <= 0)
		return (error);
	tkz_buf_init(&nbuf, buf->fd);
	error = tkz_write_token_str(&name, "", 1);
	if (tkz_is_error(error))
		return (error);
	if (tkz->env_get(tkz->data, name.mem, &value))
		error = tkz_write_buffer_str(&nbuf, value, tkz_strlen(value));
	if (!tkz_is_error(error))
		error = tkz_write_buffer_str(&nbuf, buf->mem + buf->start, buf->len);
	if (tkz_is_error(error))
	{
		tkz_free_buf(&nbuf);
		return (error);
	}
	tkz_free_buf(buf);
	*buf = nbuf;
	return (error);
}

int		tkz_subprocessor_dollar(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	int		error;
	char	c;

	if (tkz_buffer_view_char(buf, 0) != '$')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DOLLAR_SYMBOL);
	tkz_buffer_increment(buf, 1);
	error = TKZ_SUCCESS;
	if (!tkz_is_error(error) && buf->len > 0)
	{
		c = tkz_buffer_view_char(buf, 0);
		if (c == '?')
			error = tkz_subprocessor_exit_code(tkz, tkn, buf);
		else if (tkz_is_identifier(c, 1))
			error = tkz_subprocessor_env(tkz, buf);
		else if (tkz_strchr(c, "$*-@#_!0123456789"))
			tkz_buffer_increment(buf, 1);
		else
			error = tkz_write_token_str(tkn, "$", 1);
	}
	return (error);
}

int		tkz_subprocessor_normal_escape(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	c;
	int		error;

	(void)tkz;
	if (tkz_buffer_view_char(buf, 0) != '\\')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_NORMAL_ESCAPE);
	tkz_buffer_increment(buf, 1);
	c = tkz_buffer_view_char(buf, 0);
	if (c && c != '\n')
		if (tkz_is_error((error = tkz_write_token_str(tkn, &c, 1))))
			return (error);
	tkz_buffer_increment(buf, 1);
	return (TKZ_SUCCESS);
}
