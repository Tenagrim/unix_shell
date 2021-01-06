/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:08:49 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 14:09:24 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int		is_token_redirect(t_token *tkn)
{
	int		ret;

	ret = 0;
	if (tkn->len == 1 && (tkn->mem[0] == '>' || tkn->mem[0] == '<'))
		ret = 1;
	else if (tkn->len == 2 && (tkn->mem[0] == '>' && tkn->mem[1] == '>'))
		ret = 1;
	return (ret);
}

int		is_token_pipe(t_token *tkn)
{
	return (tkn->len == 1 && tkn->mem[0] == '|');
}

int		is_token_argument(t_token *tkn)
{
	return (!is_token_redirect(tkn) && !is_token_pipe(tkn));
}
