/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:40:09 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 13:57:50 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

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
		if (tkz_is_error((error =
				tkz_expand_token_memory(tkn, tkn->len + len))))
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
