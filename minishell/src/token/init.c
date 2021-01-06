/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:35:54 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 12:54:14 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int		tkz_buf_init(t_tkz_buf *buf);
t_tkz	*tkz_init(void);
void	tkz_init_token(t_token *tkn);
void	tkz_change_input_fd(t_tkz *tkz, int fd);

int		tkz_buf_init(t_tkz_buf *buf, int fd)
{
	buf->fd = fd;
	buf->start = 0;
	buf->len = 0;
	buf->cap = 32;
	buf->mem = malloc(buf->cap);
	return (!!buf->mem);
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
			if (!tkz_buf_init(&tkz->buf, STDIN_FILENO))
				tkz_free(&tkz);
		}
		else
			tkz_free(&tkz);
	}
	return (tkz);
}

void	tkz_init_token(t_token *tkn)
{
	tkn->mem = 0;
	tkn->len = 0;
	tkn->cap = 0;
}

void	tkz_change_input_fd(t_tkz *tkz, int fd)
{
	tkz->buf.fd = fd;
}
