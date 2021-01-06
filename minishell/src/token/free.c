/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:33:56 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 12:35:24 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

void	tkz_free_buf(t_tkz_buf *buf);
void	tkz_free_tokens(t_tkz *tkz);
void	tkz_free(t_tkz **tkz);
void	tkz_free_token(t_token *tkn);

void	tkz_free_buf(t_tkz_buf *buf)
{
	buf->len = 0;
	buf->start = 0;
	buf->cap = 0;
	if (buf->mem)
		free(buf->mem);
	buf->mem = 0;
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
	if (*tkz && (*tkz)->tkn)
	{
		tkz_free_tokens(*tkz);
		free((*tkz)->tkn);
	}
	if (*tkz && (*tkz)->buf.mem)
		tkz_free_buf(&(*tkz)->buf);
	if (*tkz)
		free(*tkz);
	*tkz = 0;
}

void	tkz_free_token(t_token *tkn)
{
	if (tkn->mem)
		free(tkn->mem);
	tkz_init_token(tkn);
}
