

#ifndef BUFFER_SIZE
# deifne BUFFER_SIZE 64
#endif

typedef struct	s_token
{
	int		cap;
	int		len;
	char	*mem;
}				t_token;

typedef struct s_tokenizer_buffer
{
	int			fd;
	int			start;
	int			len;
	char		mem[BUFFER_SIZE];
}				t_tkz_buf;

#define STATE_NORMAL 0
#define STATE_QUOTE 1
#define STATE_DQUOTE 2

typedef int		(*t_tkz_env_get)(void *data, char *name, char **value);
typedef int		(*t_tkz_last_exit_code)(void *data, int *exit_code);

typedef struct	s_tokenizer
{
	int			tkn_cap;
	int			tkn_count;
	t_token		*tkn;

	unsigned	state;

	t_tkz_buf	buf;

	void					*data;
	t_tkz_env_get			env_get;
	t_tkz_last_exit_code	last_exit_code;
}				t_tkz;

#define TKZ_SUCCESS (1)
#define TKZ_ERROR (-1)
#define TKZ_ERROR_PREFETCH_REQUEST_OVERFLOW (-2)
#define TKZ_ERROR_UNISTD_READ_NEGATIVE_RETURN (-3)
#define TKZ_ERROR_MALLOC_NULL_RETURN (-4)
/* internal errors (indicates bugs in library) */
#define TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_NORMAL_ESCAPE (-5)
#define TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_DQUOTE_ESCAPE (-6)
#define TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DOLLAR_SYMBOL (-7)
#define TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_QUATION_MARK_SYMBOL (-8)
#define TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_CONTROL_CHARACTER (-9)

void	tkz_buf_init(t_tkz_buf *buf)
{
	buf->fd = STDIN_FILENO;
	buf->start = 0;
	buf->len = 0;
}

void	tkz_free(t_tkz **tkz)
{
	if ((*tkz)->tkn)
		free((*tkz)->tkn);
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
		tkz->tkz_cap = 16;
		tkz->tkn = malloc(sizeof(t_token) * tkz->tkz_cap);
		if (tkz->tkn)
		{
			tkz->tkn_len = 0;
			tkz->state = 0;
			tkz_buf_init(&tkz->buf);
		}
		else
			tkz_free(&tkz);
	}
	return (tkz);
}

int		tkz_is_error(int error)
{
	return (error != TKZ_SUCCESS);
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
	int		i;

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
	if (tkn->len > 0 && tkn->str[tkn->len - 1] == '\n')
		return (1);
	return (0);
}

int		tkz_read_buffer(t_tkz_buf *buf)
{
	int		ret;

	if (buf->len > 0 && buf->start > 0)
	{
		tkz_memcpy(buf->mem, buf->mem + buf->start, buf->len);
		buf->start = 0;
	}
	if (buf->len < BUFFER_SIZE)
	{
		if ((ret = read(buf->fd, buf->mem + buf->len, BUFFER_SIZE - buf->len)))
		{
			if (ret < 0)
				return (TKZ_ERROR_UNISTD_READ_NEGATIVE_RETURN);
			buf->len += ret;
		}
	}
	return (TKZ_SUCCESS);
}

void	tkz_init_token(t_tkn *tkn)
{
	tkn->mem = 0;
	tkn->len = 0;
	tkn->cap = 0;
}

void	tkz_free_token(t_tkn *tkn)
{
	if (tkn->mem)
		free(tkn->mem);
	tkz_init_token(tkn);
}

int		tkz_is_alphanum(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z'));
}

int		tkz_is_word_sym(char c)
{
	return (is_alphanum(c) || c == '_' || c == '-')
}

int		tkz_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\r');
}

int		tkz_is_endcommand(char c)
{
	return (c == '\n' || c == ';');
}

int		tkz_is_control(char c)
{
	return (c == '$' || c == '\'' || c == '"' ||
		c == '|' || c == '<' || c == '>' || c == '=');
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
	if (tkz_buffer_view_char(buf, 1) != '?')
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
	while (!tkz_is_error(error) &&
		!tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
	{
		c = tkz_buffer_view_char(buf, 0);
		if (tkz_is_endcommand(c) || tkz_is_whitespace(c) || tkz_is_control(c))
			break ;
		else
			error = tkz_write_token_str(&name, &c, 1);
		tkz_buffer_increment(buf, 1);
	}
	if (name.len && !tkz_is_error((error = tkz_write_token_str(&name, "", 1))))
		if (tkz->env_get(tkz->data, name.mem, &value))
			error = tkz_write_token_str(tkn, value, tkz_strlen(value));
	tkz_free_token(&name);
	return (error);
}

int		tkz_subprocessor_dollar(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	c;
	int		error;

	if (tkz_buffer_view_char(buf, 0) != '$')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DOLLAR_SYMBOL);
	error = tkz_prefetch_buffer(buf, 2);
	if (!tkz_is_error(error))
	{
		if (tkz_buffer_view_char(buf, 1) == '?')
			error = tkz_subprocessor_exit_code(tkz, tkn, buf);
		else
			error = tkz_subprocessor_env(tkz, tkn, buf);
	}
	return (error);
}

int		tkz_subprocessor_normal_escape(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	c;
	int		error;

	if (tkz_buffer_view_char(buf, 0) != '\\')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_NORMAL_ESCAPE);
	tkz_buffer_increment(buf, 1);
	if (tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
		return (error);
	if (tkz_buffer_view_char(buf, 0) != '\n')
		if (tkz_is_error((error = tkz_write_token_str(tkn,
				tkz_buffer_view(buf, 0), 1))))
			return (error);
	tkz_buffer_increment(buf, 1);
	return (TKZ_SUCCESS);
}

int		tkz_subprocessor_dquote_escape(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	c;
	int		error;

	if (tkz_buffer_view_char(buf, 0) != '\\')
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_DQUOTE_ESCAPE);
	tkz_buffer_increment(buf, 1);
	if (tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
		return (error);
	c = tkz_buffer_view_char(buf, 0);
	if (c == '"' || c == '\\' || c == '`' || c == '\n')
		if (!tkz_is_error((error = tkz_write_token_str(tkn,
				tkz_buffer_view(buf, 0), 1))))
			tkz_buffer_increment(buf, 1);
	else
		error = tkz_write_token_str(tkn, tkz_buffer_view(buf, 0), 1);
	return (error);
}

void	tkz_token_move_char_from_buffer(t_token *tkn, t_tkz_buf *buf)
{
	char	c;

	c = tkz_buffer_view_char(buf, 0);
	if (c)
	{
		tkz_write_token_str(tkn, &c, 1);
		tkz_buffer_increment(buf, 1);
	}
}

int		tkz_subprocessor_control(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	char	c;
	int		error;

	error = TKZ_SUCCESS;
	c = tkz_buffer_view_char(buf, 0);
	if (!tkz_is_control(c))
		return (TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_CONTROL_CHARACTER);
	tkz_buffer_increment(buf, 1);
	if (c == '>')
		if (!tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
			if (tkz_buffer_view_char(buf, 1) == '>')
				tkz_token_move_char_from_buffer(tkn, buf);
	return (error);
}

int		tkz_processor_normal(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf)
{
	int		error;
	char	c;

	error = TKZ_SUCCESS;
	while (!tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
	{
		c = tkz_buffer_view_char(buf, 0);
		else if (c == '$')
			error = tkz_subprocessor_dollar(tkz, tkn, buf);
		else if (c == '\\')
			error = tkz_subprocessor_normal_escape(tkz, tkn, buf);
		else if (tkz_is_endcommand(c) || tkz_is_whitespace(c) || tkz_is_control(c))
			break ;
		else
			error = tkz_write_token_str(tkn, &c, 1);
		if (tkz_is_error(error))
			return (error);
		tkz_buffer_increment(buf, 1);
	}
	if (c == '\'')
		tkz->state = STATE_QUOTE;
	else if (c == '"')
		tkz->state = STATE_DQUOTE;
	else if (tkz_is_control(c) && tkn->len == 0)
		error = tkz_subprocessor_control(tkz, tkn, buf);
	return (error);
}

int		tkz_processor_quote(t_tkz *tkz, t_tkn *tkn, t_tkz_buf *buf)
{
	int		error;
	char	c;

	error = TKZ_SUCCESS;
	while (!tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
	{
		c = tkz_buffer_view_char(buf, 0);
		else if (c == '\'' || c == '\n')
			break ;
		else
			error = tkz_write_token_str(tkn, &c, 1);
		if (tkz_is_error(error))
			break ;
		tkz_buffer_increment(buf, 1);
	}
	if (!tkz_is_error(error) && c == '\'')
		tkz_buffer_increment(buf, 1);
	tkz->state = STATE_NORMAL;
	return (error);
}

int		tkz_processor_dquote(t_tkz *tkz, t_tkn *tkn, t_tkz_buf *buf)
{
	int		error;
	char	c;

	error = TKZ_SUCCESS;
	while (!tkz_is_error((error = tkz_prefetch_buffer(buf, 1))))
	{
		c = tkz_buffer_view_char(buf, 0);
		else if (c == '$')
			error = tkz_subprocessor_dollar(tkz, tkn, buf);
		else if (c == '\n' || c == '"')
			break ;
		else if (c == '\\')
			error = tkz_subprocessor_dquote_escape(tkz, tkn, buf);
		else
			error = tkz_write_token_str(tkn, &c, 1);
		if (tkz_is_error(error))
			break ;
		tkz_buffer_increment(buf, 1);
	}
	if (!tkz_is_error(error) && c == '"')
		tkz_buffer_increment(buf, 1);
	tkz->state = STATE_NORMAL;
	return (error);
}

int		tkz_buffer_skip_whitespaces_with_prefetching(t_tkz_buf *buf)
{
	char	c;
	int		error;

	error = TKZ_SUCCESS;
	while (!tkz_is_error(error) &&
			(c = tkz_buffer_view_char(buf, 0)) && !tkz_is_endcommand(c) &&
			tkz_is_whitespace(c))
	{
		tkz_buffer_increment(buf, 1);
		error = tkz_prefetch_buffer(buf, 1);
	}
	return (error);
}

void	tkz_buffer_skip_whitespaces(t_tkz_buf *buf)
{
	char c;

	while ((c = tkz_buffer_view_char(buf, 0)) && !tkz_is_endcommand(c) &&
			tkz_is_whitespace(c))
		tkz_buffer_increment(buf, 1);
}

int		tkz_buffer_is_endcommand(t_tkz_buf *buf)
{
	char c;

	while ((c = tkz_buffer_view_char(buf, 0)) && !tkz_is_endcommand(c) &&
			tkz_is_whitespace(c))
		tkz_buffer_increment(buf, 1);
	return (tkz_is_endcommand(c));
}

void	tkz_buffer_skip_endcommand(t_tkz_buf *buf)
{
	if (tkz_buffer_is_endcommand(buf))
		tkz_buffer_increment(buf, 1);
}

int		tkz_make_token(t_tkz *tkz, int i_tkn, int *remains)
{
	t_token	*tkn;
	int		error;

	tkn = &tkz->tkn[i_tkn];
	tkz_init_token(tkn);
	error = tkz_buffer_skip_whitespaces_with_prefetching(buf);
	tkz->state = STATE_NORMAL;
	while (!tkz_is_error(error) &&
		(tkz->state == STATE_NORMAL &&
		!tkz_is_error((error = tkz_processor_normal(tkz, tkn, &tkz->buf)))) ||
		(tkz->state == STATE_QUOTE &&
		!tkz_is_error((error = tkz_processor_quote(tkz, tkn, &tkz->buf)))) ||
		(tkz->state == STATE_DQUOTE &&
		!tkz_is_error((error = tkz_processor_dquote(tkz, tkn, &tkz->buf)))))
	{
	}
	if (!tkz_is_error(error))
		*remains = !tkz_buffer_is_endcommand(&tkz->buf);
	return (error);
}

int		tkz_make(t_tkz *tkz)
{
	int		remains;

	tkz->tkn_count = 0
	error = tkz_make_token(tkz, tkz->tkn_count++, &remains);
	while (!tkz_is_error(error) && remains)
	{
		if (tkz->tkn_count >= tkz->tkn_cap)
			if (tkz_is_error((error = tkz_expand_tokens_array(tkz))))
				return (error);
		error = tkz_make_token(tkz, tkz->tkn_count++, &remains);
	}
	if (!tkz_is_error(error))
		tkz_buffer_skip_endcommand(&tkz->buf);
	return (TKZ_SUCCESS);
}



