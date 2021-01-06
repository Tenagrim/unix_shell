/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprocessor2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:54:44 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 13:47:29 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int		tkz_subprocessor_dquote_escape(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	c;
	int		error;

	(void)tkz;
	if (tkz_buffer_view_char(buf, 0) != '\\')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_DQUOTE_ESCAPE);
	error = TKZ_SUCCESS;
	c = tkz_buffer_view_char(buf, 1);
	if (c == 0 || c == '"' || c == '\\' || c == '`' || c == '\n' || c == '$')
	{
		if (c && !tkz_is_error((error = tkz_write_token_str(tkn, &c, 1))))
			tkz_buffer_increment(buf, 2);
	}
	else
		error = tkz_token_move_char_from_buffer(tkn, buf);
	return (error);
}

int		tkz_subprocessor_control(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	c;
	int		error;

	error = TKZ_SUCCESS;
	c = tkz_buffer_view_char(buf, 0);
	if (!c)
		return (TKZ_SUCCESS);
	if (!tkz_is_control(c))
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_CONTROL_CHARACTER);
	error = tkz_token_move_char_from_buffer(tkn, buf);
	if (!tkz_is_error(error) && c == '>')
		if (buf->len > 0)
			if (tkz_buffer_view_char(buf, 0) == '>')
				error = tkz_token_move_char_from_buffer(tkn, buf);
	if (!tkz_is_error(error))
		tkz->state = STATE_TERMINATE;
	return (error);
}

int		tkz_subprocessor_dquote_end(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	c;
	int		error;

	(void)tkn;
	error = TKZ_SUCCESS;
	c = tkz_buffer_view_char(buf, 0);
	if (c == '\n')
	{
		error = TKZ_ERROR_UNEXPECTED_EOF_WHILE_DQUOTE;
		tkz->flags |= TKZ_FLAG_QUOTE_NL_END;
	}
	return (error);
}
