/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:22:59 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 13:33:24 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

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
