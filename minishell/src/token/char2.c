/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:40:46 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 12:40:47 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int		tkz_is_word(char c);
int		tkz_is_identifier(char c, int is_begin);

int		tkz_is_word(char c)
{
	return (!tkz_is_endcommand(c) && !tkz_is_wp(c) && !tkz_is_control(c) &&
			!tkz_is_quote(c) && c != '$');
}

int		tkz_is_identifier(char c, int is_begin)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' ||
		(!is_begin && c >= '0' && c <= '9'));
}
