

#ifndef BUFFER_SIZE
# deifne BUFFER_SIZE 64
#endif

typedef struct	s_token
{
	int		cap;
	int		len;
	char	*str;
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
#define STATE_SUB 3

typedef struct	s_tokenizer
{
	int			tkn_cap;
	int			tkn_count;
	t_token		*tkn;

	unsigned	state;

	t_tkz_buf	buf;
}				t_tkz;

#define TKZ_SUCCESS 1
#define TKZ_ERROR (-1)
#define TKZ_IS_ERROR(code) ((code) == TKZ_ERROR)





t_tkz	*tkz_init(void)
{
	t_tkz *tkz;

	tkz = malloc(sizeof(t_tkz));
	tkz->tkz_cap = 16;
	tkz->tkn = malloc(sizeof(t_token) * tkz->tkz_cap);
	tkz->tkn_len = 0;
	tkz->state = 0;
}

void	tkz_free(t_tkz **tkz)
{
	if ((*tkz)->tkn)
		free((*tkz)->tkn);
	if (*tkz)
		free(*tkz);
	*tkz = 0;
}

int		tkz_error(t_tkz *tkz)
{
	return (TKZ_ERROR);
}

int		tkz_expand_tokens_array(t_tkz *tkz)
{
	int		new_cap;
	t_token	*new_ptr;
	int		i;

	new_cap = tkz->tkn_cap * 2;
	if (new_cap <= 0)
		return (TKZ_ERROR);
	new_ptr = malloc(new_cap * sizeof(t_token));
	if (!new_ptr)
		return (TKZ_ERROR);
	if (tkz->tkn)
	{
		i = 0;
		while (i < tkz->tkn_count)
		{
			new_ptr[i] = tkz->tkn[i];
			i += 1;
		}
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

void	tkz_memcpy(void *l, void *r, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		((char *)l)[i] = ((char *)r)[i];
		i += 1;
	}
}

int		tkz_read_buffer(t_tkz_buf *buf)
{
	int		ret;

	if (buf->len - buf->start > 0)
	{
		tkz_memcpy(buf->mem, buf->mem + buf->start, buf->len);
		buf->start = 0;
	}
	if (buf->len < BUFFER_SIZE)
	{
		if ((ret = read(buf->fd, buf->mem + buf->len, BUFFER_SIZE - buf->len)))
		{
			if (ret < 0)
				return (TKZ_ERROR);
			buf->len += ret;
		}
	}
	return (TKZ_SUCCESS);
}

int		tkz_read_token(t_tkn *tkn, t_tkz_buf *buf)
{

}

void	tkn_init(t_tkn *tkn)
{
	tkn->str = 0;
	tkn->len = 0;
	tkn->cap = 0;
}

int		is_alphanum(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z'));
}

int		is_word_sym(char c)
{
	return (is_alphanum(c) || c == '_')
}

int		tkz_bufview_if_word(t_tkz_buf *buf)
{

}

int		tkz_processor_normal(tkn, &tkz->buf)
{

}

int		tkz_make_token(t_tkz *tkz, int i_tkn)
{
	t_token	*tkn;

	tkn = &tkz->tkn[i_tkn];
	tkn_init(tkn);
	while ((tkz->state == STATE_NORMAL && tkz_processor_normal(tkn, &tkz->buf)) ||
			(tkz->state == STATE_QUOTE && tkz_processor_quote(tkn, &tkz->buf)) ||
			(tkz->state == STATE_DQUOTE && tkz_processor_dquote(tkn, &tkz->buf)) ||
			(tkz->state == STATE_SUB && tkz_processor_sub(tkn, &tkz->buf)))
	{
	}

	if (TKZ_IS_ERROR(tkz_read_token(tkn, &tkz->buf)))
		return (TKZ_ERROR);
	while (!tkz_check_token_end_condition(tkz))
	{
		if (TKZ_IS_ERROR(tkz_read_buffer(&tkz->buf)))
			return (TKZ_ERROR);
		if (TKZ_IS_ERROR(tkz_read_token(tkn, &tkz->buf)))
			return (TKZ_ERROR);
	}
	return (tkz_remains(&tkz->buf));
}

int		make_tkz(t_tkz *tkz)
{
	int		remains;

	tkz->tkn_count = 0
	remains = tkz_make_token(tkz, tkz->tkn_count++);
	if (TKZ_IS_ERROR(remains))
		return tkz_error(tkz);
	while (remains)
	{
		if (tkz->tkn_count >= tkz->tkn_cap)
			if (TKZ_IS_ERROR(tkz_expand_tokens_array(tkz)))
				return (tkz_error(tkz));
		remains = tkz_make_token(tkz, tkz->tkn_count++);
		if (TKZ_IS_ERROR(remains))
			return (tkz_error(tkz));
	}
	return (TKZ_SUCCESS);
}



