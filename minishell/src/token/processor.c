/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:59:48 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 13:33:15 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int		tkz_processor_normal(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	int		error;
	char	c;

	error = TKZ_SUCCESS;
	while (!tkz_is_error(error) && buf->len > 0)
	{
		c = tkz_buffer_view_char(buf, 0);
		if (c == '$')
			error = tkz_subprocessor_dollar(tkz, tkn, buf);
		else if (c == '\\')
			error = tkz_subprocessor_normal_escape(tkz, tkn, buf);
		else if (!tkz_is_word(c))
			break ;
		else
			error = tkz_token_move_char_from_buffer(tkn, buf);
	}
	if (!tkz_is_error(error))
		tkz_update_state(tkz, buf);
	if (!tkz_is_error(error) && tkz_is_control(c) && tkn->len == 0)
		error = tkz_subprocessor_control(tkz, tkn, buf);
	return (error);
}

int		tkz_processor_quote(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	int		error;
	char	c;

	tkz_buffer_increment(buf, 1);
	error = TKZ_SUCCESS;
	while (!tkz_is_error(error) && buf->len > 0)
	{
		c = tkz_buffer_view_char(buf, 0);
		if (c == '\'' || c == '\n')
		{
			if (c == '\n')
			{
				error = TKZ_ERROR_UNEXPECTED_EOF_WHILE_QUOTE;
				tkz->flags |= TKZ_FLAG_QUOTE_NL_END;
			}
			break ;
		}
		error = tkz_token_move_char_from_buffer(tkn, buf);
	}
	if (!tkz_is_error(error) && c == '\'')
		tkz_buffer_increment(buf, 1);
	if (!tkz_is_error(error))
		tkz_update_state(tkz, buf);
	return (error);
}

int		tkz_processor_dquote(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	int		error;
	char	c;

	tkz_buffer_increment(buf, 1);
	error = TKZ_SUCCESS;
	while (!tkz_is_error(error) && buf->len > 0)
	{
		c = tkz_buffer_view_char(buf, 0);
		if (c == '$')
			error = tkz_subprocessor_dollar(tkz, tkn, buf);
		else if (c == '\n' || c == '"')
		{
			error = tkz_subprocessor_dquote_end(tkz, tkn, buf);
			break ;
		}
		else if (c == '\\')
			error = tkz_subprocessor_dquote_escape(tkz, tkn, buf);
		else
			error = tkz_token_move_char_from_buffer(tkn, buf);
	}
	if (!tkz_is_error(error) && c == '"')
		tkz_buffer_increment(buf, 1);
	if (!tkz_is_error(error))
		tkz_update_state(tkz, buf);
	return (error);
}
