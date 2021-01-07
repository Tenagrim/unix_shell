/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:24:53 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/07 17:01:26 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

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
