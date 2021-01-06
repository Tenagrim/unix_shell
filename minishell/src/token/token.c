/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:40:09 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 12:54:52 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "token.h"
#include <stdio.h>

int		tkz_expand_tokens_array(t_tkz *tkz)
{
	int		new_cap;
	t_token	*new_ptr;

	new_cap = tkz->tkn_cap * 2;
	if (new_cap <= 0)
		new_cap = 16;
	new_ptr = malloc(new_cap * sizeof(t_token));
	if (!new_ptr)
		return (TKZ_ERROR_MALLOC_NULL_RETURN);
	if (tkz->tkn)
	{
		tkz_memcpy(new_ptr, tkz->tkn, tkz->tkn_count * sizeof(t_token));
		free(tkz->tkn);
	}
	tkz->tkn = new_ptr;
	tkz->tkn_cap = new_cap;
	return (TKZ_SUCCESS);
}

int		tkz_expand_token_memory(t_token *tkn, int min)
{
	int		new_cap;
	char	*new_mem;

	new_cap = tkn->cap * 2;
	if (new_cap <= 0)
		new_cap = 16;
	if (new_cap < min)
		new_cap += min;
	new_mem = malloc(new_cap);
	if (!new_mem)
		return (TKZ_ERROR_MALLOC_NULL_RETURN);
	if (tkn->mem)
	{
		tkz_memcpy(new_mem, tkn->mem, tkn->len);
		free(tkn->mem);
	}
	tkn->mem = new_mem;
	tkn->cap = new_cap;
	return (TKZ_SUCCESS);
}

int		tkz_write_token_str(t_token *tkn, char *str, int len)
{
	int		error;

	if (tkn->len + len > tkn->cap)
		if (tkz_is_error((error = tkz_expand_token_memory(tkn, tkn->len + len))))
			return (error);
	tkz_memcpy(tkn->mem + tkn->len, str, len);
	tkn->len += len;
	return (TKZ_SUCCESS);
}

int		tkz_token_move_char_from_buffer(t_token *tkn, t_tkz_buf *buf)
{
	char	c;
	int		error;

	error = TKZ_SUCCESS;
	c = tkz_buffer_view_char(buf, 0);
	if (c)
	{
		error = tkz_write_token_str(tkn, &c, 1);
		if (!tkz_is_error(error))
			tkz_buffer_increment(buf, 1);
	}
	return (error);
}


void	tkz_update_state(t_tkz *tkz, t_tkz_buf *buf)
{
	char	c;

	if (buf->len > 0)
	{
		c = tkz_buffer_view_char(buf, 0);
		if (c == '\'')
			tkz->state = STATE_QUOTE;
		else if (c == '"')
			tkz->state = STATE_DQUOTE;
		else if (tkz_is_word(c) || c == '$')
			tkz->state = STATE_NORMAL;
		else
			tkz->state = STATE_TERMINATE;
		if (tkz->state == STATE_QUOTE || tkz->state == STATE_DQUOTE)
			tkz->flags |= TKZ_FLAG_QUOTED;
	}
	else
		tkz->state = STATE_TERMINATE;
}

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

int		tkz_make_token(t_tkz *tkz, int i_tkn, int *remains)
{
	t_token	*tkn;
	int		error;

	tkn = &tkz->tkn[i_tkn];
	tkz_init_token(tkn);
	tkz->state = STATE_NORMAL;
	error = tkz_buffer_read_command(tkz, &tkz->buf);
	while (!tkz_is_error(error) && tkz->state != STATE_TERMINATE)
	{
		if (tkz->state == STATE_NORMAL)
			error = tkz_processor_normal(tkz, tkn, &tkz->buf);
		if (tkz->state == STATE_QUOTE)
			error = tkz_processor_quote(tkz, tkn, &tkz->buf);
		if (tkz->state == STATE_DQUOTE)
			error = tkz_processor_dquote(tkz, tkn, &tkz->buf);
	}
	if (!tkz_is_error(error) && !tkn->len && !(tkz->flags & TKZ_FLAG_QUOTED))
		tkz->tkn_count -= 1;
	if (!tkz_is_error(error))
		*remains = tkz->buf.len > 0 && !tkz_buffer_is_endcommand(&tkz->buf);
	tkz->flags &= ~TKZ_FLAG_QUOTED;
	return (error);
}

int		tkz_make(t_tkz *tkz)
{
	int		remains;
	int		error;

	tkz_free_tokens(tkz);
	tkz->flags = 0;
	error = tkz_make_token(tkz, tkz->tkn_count++, &remains);
	while (!tkz_is_error(error) && remains)
	{
		if (tkz->tkn_count >= tkz->tkn_cap)
			if (tkz_is_error((error = tkz_expand_tokens_array(tkz))))
				return (error);
		error = tkz_make_token(tkz, tkz->tkn_count++, &remains);
	}
	tkz_buffer_full_skip_endcommand(&tkz->buf);
	return (error);
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

int		tkz_check_flags(t_tkz *tkz, int flags)
{
	return (tkz->flags & flags);
}

void	tkz_print_buf(t_tkz_buf *buf)
{
	printf("buffer state:\n");
	printf(" - fd: %d;\n - start: %d;\n - len: %d\n - cap: %d\n", buf->fd, buf->start, buf->len, buf->cap);
	printf(" - mem: [%.*s]\n", buf->len, buf->mem + buf->start);
}

void	tkz_print_token(t_token *tkn)
{
	printf("token<%2d:%2d>[%.*s]\n", tkn->len, tkn->cap, tkn->len, tkn->mem);
}

void	tkz_print(t_tkz *tkz)
{
	int		i;

	tkz_print_buf(&tkz->buf);
	printf("state: %u\n", tkz->state);
	printf("tokens capacity: %d\n", tkz->tkn_cap);
	printf("tokens count: %d\n", tkz->tkn_count);
	i = 0;
	while (i < tkz->tkn_count)
	{
		printf("%2d: ", i);
		tkz_print_token(&tkz->tkn[i]);
		i += 1;
	}
}

void	tkz_print_lite(t_tkz *tkz)
{
	int		i;

	i = 0;
	while (i < tkz->tkn_count)
	{
		printf("%2d: ", i);
		tkz_print_token(&tkz->tkn[i]);
		i += 1;
	}
}


