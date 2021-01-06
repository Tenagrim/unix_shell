/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:27:18 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 13:56:48 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdio.h>

void	tkz_print_buf(t_tkz_buf *buf)
{
	printf("buffer state:\n");
	printf(" - fd: %d;\n - start: %d;\n - len: %d\n - cap: %d\n",
		buf->fd, buf->start, buf->len, buf->cap);
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
