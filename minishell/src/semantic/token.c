/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:09:28 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 14:52:27 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

t_token	*get_current_token(t_super *sp)
{
	t_token	*tkn;

	tkn = 0;
	if (sp->current_token >= 0 && sp->current_token < sp->tkz->tkn_count)
		tkn = &sp->tkz->tkn[sp->current_token];
	return (tkn);
}

t_token	*get_offseted_token(t_super *sp, int offset)
{
	int		token_start;
	t_token	*tkn;

	token_start = sp->current_token;
	sp->current_token += offset;
	tkn = get_current_token(sp);
	sp->current_token = token_start;
	return (tkn);
}

void	increment_token_pointer(t_super *sp)
{
	if (sp->current_token < sp->tkz->tkn_count)
		sp->current_token += 1;
}

void	move_token_pointer(t_super *sp, int offset)
{
	sp->current_token += offset;
}

int		token_compare(t_token *tkn, const char *str, int len)
{
	int		i;

	if (tkn->len != len)
		return (0);
	i = 0;
	while (i < len && i < tkn->len && tkn->mem[i] == str[i])
		i += 1;
	return (i >= len);
}
