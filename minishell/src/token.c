/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:40:09 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/03 11:56:27 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "token.h"
#include <stdio.h>

void	tkz_buf_init(t_tkz_buf *buf)
{
	buf->fd = STDIN_FILENO;
	buf->start = 0;
	buf->len = 0;
}

void	tkz_free_tokens(t_tkz *tkz)
{
	int		i;

	if (tkz->tkn && tkz->tkn_count > 0)
	{
		i = 0;
		while (i < tkz->tkn_count)
		{
			if (tkz->tkn[i].mem)
				free(tkz->tkn[i].mem);
			i += 1;
		}
	}
	tkz->tkn_count = 0;
}

void	tkz_free(t_tkz **tkz)
{
	if ((*tkz)->tkn)
	{
		tkz_free_tokens(*tkz);
		free((*tkz)->tkn);
	}
	if (*tkz)
		free(*tkz);
	*tkz = 0;
}

t_tkz	*tkz_init(void)
{
	t_tkz *tkz;

	tkz = malloc(sizeof(t_tkz));
	if (tkz)
	{
		tkz->tkn_cap = 16;
		tkz->tkn_count = 0;
		tkz->tkn = malloc(sizeof(t_token) * tkz->tkn_cap);
		if (tkz->tkn)
		{
			tkz->state = 0;
			tkz_buf_init(&tkz->buf);
		}
		else
			tkz_free(&tkz);
	}
	return (tkz);
}

void	tkz_change_input_fd(t_tkz *tkz, int fd)
{
	tkz->buf.fd = fd;
}

int		tkz_is_error(int error)
{
	return (error != TKZ_SUCCESS);
}

typedef const char t_cchar;

t_cchar	*tkz_error_str(int error)
{
	if (error == TKZ_ERROR)
		return ("unrecognized error.");
	else if (error == TKZ_ERROR_PREFETCH_REQUEST_OVERFLOW)
		return ("prefetch request overflow");
	else if (error == TKZ_ERROR_UNISTD_READ_NEGATIVE_RETURN)
		return ("unistd read negative return");
	else if (error == TKZ_ERROR_UNISTD_READ_EOF)
		return ("unistd read eof");
	else if (error == TKZ_ERROR_MALLOC_NULL_RETURN)
		return ("malloc null return");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_NORMAL_ESCAPE)
		return ("contract is terminated for backslash normal escape");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_DQUOTE_ESCAPE)
		return ("contract is terminated for backslash dquote escape");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DOLLAR_SYMBOL)
		return ("contract is terminated for dollar symbol");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_QUATION_MARK_SYMBOL)
		return ("contract is terminated for quation mark symbol");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_CONTROL_CHARACTER)
		return ("contract is terminated for control character");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_QUOTE_SYMBOL)
		return ("contract is terminated for quote symbol");
	if (error == TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DQUOTE_SYMBOL)
		return ("contract is terminated for dquote symbol");
	return ("undefined value");
}

int		tkz_is_wp(char c)
{
	return (c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\r');
}

int		tkz_is_endcommand(char c)
{
	return (c == '\n' || c == ';');
}

int		tkz_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int		tkz_is_control(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int		tkz_is_word(char c)
{
	return (!tkz_is_endcommand(c) && !tkz_is_wp(c) && !tkz_is_control(c) &&
			!tkz_is_quote(c));
}

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

int		tkz_check_token_end_condition(t_tkz *tkz, t_token *tkn)
{
	if (tkz->state != 0)
		return (0);
	if (tkn->len > 0 && tkz_is_endcommand(tkn->mem[tkn->len - 1]))
		return (1);
	return (0);
}

int		tkz_read_buffer(t_tkz_buf *buf)
{
	int		ret;

	if (buf->len > 0 && buf->start > 0)
		tkz_memcpy(buf->mem, buf->mem + buf->start, buf->len);
	buf->start = 0;
	if (buf->len < BUFFER_SIZE)
	{
		ret = read(buf->fd, buf->mem + buf->len, BUFFER_SIZE - buf->len);
		if (ret < 0)
			return (TKZ_ERROR_UNISTD_READ_NEGATIVE_RETURN);
		if (ret == 0)
			return (TKZ_ERROR_UNISTD_READ_EOF);
		buf->len += ret;
	}
	return (TKZ_SUCCESS);
}

void	tkz_init_token(t_token *tkn)
{
	tkn->mem = 0;
	tkn->len = 0;
	tkn->cap = 0;
}

void	tkz_free_token(t_token *tkn)
{
	if (tkn->mem)
		free(tkn->mem);
	tkz_init_token(tkn);
}

int		tkz_prefetch_buffer(t_tkz_buf *buf, int count)
{
	if (count > BUFFER_SIZE - buf->len)
		return (TKZ_ERROR_PREFETCH_REQUEST_OVERFLOW);
	if (count > buf->len)
		return (tkz_read_buffer(buf));
	return (TKZ_SUCCESS);
}

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

int		tkz_subprocessor_exit_code(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	numbuf[24];
	int		numlen;
	int		exit_code;
	int		error;

	if (tkz_buffer_view_char(buf, 0) != '$')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DOLLAR_SYMBOL);
	tkz_buffer_increment(buf, 1);
	if (tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
		return (error);
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

int		tkz_subprocessor_env(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	c;
	int		error;
	char	*value;
	t_token	name;

	if (tkz_buffer_view_char(buf, 0) != '$')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DOLLAR_SYMBOL);
	tkz_buffer_increment(buf, 1);
	tkz_init_token(&name);
	error = TKZ_SUCCESS;
	while (!tkz_is_error(error) &&
		!tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
	{
		c = tkz_buffer_view_char(buf, 0);
		if (!tkz_is_word(c))
			break ;
		error = tkz_token_move_char_from_buffer(&name, buf);
	}
	if (!tkz_is_error(error))
		if (name.len && !tkz_is_error((error =
				tkz_write_token_str(&name, "", 1))))
			if (tkz->env_get(tkz->data, name.mem, &value))
				error = tkz_write_token_str(tkn, value, tkz_strlen(value));
	tkz_free_token(&name);
	return (error);
}

int		tkz_subprocessor_dollar(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	int		error;
	char	c;

	if (tkz_buffer_view_char(buf, 0) != '$')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DOLLAR_SYMBOL);
	error = tkz_prefetch_buffer(buf, 2);
	if (!tkz_is_error(error))
	{
		c = tkz_buffer_view_char(buf, 1);
		if (c == '?')
			error = tkz_subprocessor_exit_code(tkz, tkn, buf);
		else if (tkz_is_word(c))
			error = tkz_subprocessor_env(tkz, tkn, buf);
		else
			error = TKZ_ERROR_INVALID_DOLLAR_SYNTAX;
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
	if (tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
		return (error);
	c = tkz_buffer_view_char(buf, 0);
	if (c != '\n')
		if (tkz_is_error((error = tkz_write_token_str(tkn, &c, 1))))
			return (error);
	tkz_buffer_increment(buf, 1);
	return (TKZ_SUCCESS);
}

int		tkz_subprocessor_dquote_escape(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	c;
	int		error;
	(void)tkz;

	if (tkz_buffer_view_char(buf, 0) != '\\')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_DQUOTE_ESCAPE);
	if (tkz_is_error((error = tkz_prefetch_buffer(buf, 2))))
		return (error);
	c = tkz_buffer_view_char(buf, 1);
	if (c == '"' || c == '\\' || c == '`' || c == '\n')
	{
		if (!tkz_is_error((error = tkz_write_token_str(tkn, &c, 1))))
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
	if (tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
		return (error);
	c = tkz_buffer_view_char(buf, 0);
	if (!tkz_is_control(c))
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_CONTROL_CHARACTER);
	error = tkz_token_move_char_from_buffer(tkn, buf);
	if (!tkz_is_error(error) && c == '>')
		if (!tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
			if (tkz_buffer_view_char(buf, 0) == '>')
				error = tkz_token_move_char_from_buffer(tkn, buf);
	if (!tkz_is_error(error))
		tkz->state = STATE_TERMINATE;
	return (error);
}

int		tkz_update_state(t_tkz *tkz, t_tkz_buf *buf)
{
	char	c;
	int		error;

	if (!tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
	{
		c = tkz_buffer_view_char(buf, 0);
		if (c == '\'')
			tkz->state = STATE_QUOTE;
		else if (c == '"')
			tkz->state = STATE_DQUOTE;
		else
			tkz->state = STATE_NORMAL;
	}
	return (error);
}

int		tkz_processor_normal(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	int		error;
	char	c;

	error = TKZ_SUCCESS;
	while (!tkz_is_error(error) &&
		!tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
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
		error = tkz_update_state(tkz, buf);
	if (!tkz_is_error(error) && tkz_is_control(c) && tkn->len == 0)
		error = tkz_subprocessor_control(tkz, tkn, buf);
	return (error);
}

int		tkz_processor_quote(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	int		error;
	char	c;

	if (tkz_buffer_view_char(buf, 0) != '\'')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_QUOTE_SYMBOL);
	tkz_buffer_increment(buf, 1);
	error = TKZ_SUCCESS;
	while (!tkz_is_error(error) &&
		!tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
	{
		c = tkz_buffer_view_char(buf, 0);
		if (c == '\'' || c == '\n')
			break ;
		error = tkz_token_move_char_from_buffer(tkn, buf);
	}
	if (!tkz_is_error(error) && c == '\'')
		tkz_buffer_increment(buf, 1);
	if (!tkz_is_error(error))
		error = tkz_update_state(tkz, buf);
	return (error);
}

int		tkz_processor_dquote(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	int		error;
	char	c;

	if (tkz_buffer_view_char(buf, 0) != '"')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DQUOTE_SYMBOL);
	tkz_buffer_increment(buf, 1);
	error = TKZ_SUCCESS;
	while (!tkz_is_error(error) &&
		!tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
	{
		c = tkz_buffer_view_char(buf, 0);
		if (c == '$')
			error = tkz_subprocessor_dollar(tkz, tkn, buf);
		else if (c == '\n' || c == '"')
			break ;
		else if (c == '\\')
			error = tkz_subprocessor_dquote_escape(tkz, tkn, buf);
		else
			error = tkz_token_move_char_from_buffer(tkn, buf);
	}
	if (!tkz_is_error(error) && c == '"')
		tkz_buffer_increment(buf, 1);
	if (!tkz_is_error(error))
		error = tkz_update_state(tkz, buf);
	return (error);
}

int		tkz_skip_whitespaces_with_prefetching(t_tkz *tkz)
{
	char	c;
	int		error;

	error = tkz_prefetch_buffer(&tkz->buf, 1);
	while (!tkz_is_error(error) &&
			(c = tkz_buffer_view_char(&tkz->buf, 0)) && !tkz_is_endcommand(c) &&
			tkz_is_wp(c))
	{
		if (tkz->tkn_count == 1)
			tkz->flags |= TKZ_FLAG_WS_AT_START;
		tkz_buffer_increment(&tkz->buf, 1);
		error = tkz_prefetch_buffer(&tkz->buf, 1);
	}
	return (error);
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

void	tkz_buffer_skip_endcommand(t_tkz_buf *buf)
{
	if (tkz_buffer_is_endcommand(buf))
		tkz_buffer_increment(buf, 1);
}

void	tkz_buffer_full_skip_endcommand(t_tkz_buf *buf)
{
	char c;

	while ((c = tkz_buffer_view_char(buf, 0)) && !tkz_is_endcommand(c))
		tkz_buffer_increment(buf, 1);
	tkz_buffer_increment(buf, 1);
}

int		tkz_token_continue_condition(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	c;
	int		condition;
	(void)tkn;

	condition = 1;
	c = tkz_buffer_view_char(buf, 0);
	if (!tkz_is_word(c) || tkz->state == STATE_TERMINATE)
		condition = 0;
	return (condition);
}

int		tkz_make_token(t_tkz *tkz, int i_tkn, int *remains)
{
	t_token	*tkn;
	int		error;
	int		condition;

	tkn = &tkz->tkn[i_tkn];
	tkz_init_token(tkn);
	error = tkz_skip_whitespaces_with_prefetching(tkz);
	tkz->state = STATE_NORMAL;
	condition = tkz_token_continue_condition(tkz, tkn, &tkz->buf);
	while (!tkz_is_error(error) && condition)
	{
		do {
			if (tkz->state == STATE_NORMAL)
				error = tkz_processor_normal(tkz, tkn, &tkz->buf);
			if (tkz->state == STATE_QUOTE)
				error = tkz_processor_quote(tkz, tkn, &tkz->buf);
			if (tkz->state == STATE_DQUOTE)
				error = tkz_processor_dquote(tkz, tkn, &tkz->buf);
			if (tkz->state == STATE_TERMINATE)
				break ;
		} while (tkz->state != STATE_NORMAL);
		if (!tkz_is_error(error))
			condition = tkz_token_continue_condition(tkz, tkn, &tkz->buf);
	}
	if (!tkz_is_error(error))
		*remains = !tkz_buffer_is_endcommand(&tkz->buf);
	return (error);
}

void	tkz_remove_last_empty_tokens(t_tkz *tkz)
{
	while (tkz->tkn_count - 1 >= 0 && tkz->tkn[tkz->tkn_count - 1].len <= 0)
	{
		if (tkz->tkn[tkz->tkn_count - 1].mem)
			free(tkz->tkn[tkz->tkn_count - 1].mem);
		tkz->tkn_count -= 1;
	}
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
	tkz_remove_last_empty_tokens(tkz);
	if (tkz_is_error(error) && (error == TKZ_ERROR_UNISTD_READ_EOF &&
			(tkz->tkn_count != 0 || tkz->flags & TKZ_FLAG_WS_AT_START)))
	{
		tkz->flags |= TKZ_FLAG_UNEXPECTED_EOF;
		error = TKZ_SUCCESS;
	}
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
	return (result);
}

int		tkz_check_flags(t_tkz *tkz, int flags)
{
	return (tkz->flags & flags);
}

void	tkz_print_buf(t_tkz_buf *buf)
{
	printf("buffer state:\n");
	printf(" - fd: %d;\n - start: %d;\n - len: %d\n - cap: %d\n", buf->fd, buf->start, buf->len, BUFFER_SIZE);
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


