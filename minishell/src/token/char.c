/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:39:08 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 12:41:25 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int		tkz_is_wp(char c);
int		tkz_is_endcommand(char c);
int		tkz_is_quote(char c);
int		tkz_is_control(char c);

int		tkz_is_wp(char c)
{
	return (c == ' ' || c == '\t' || c == '\f' || c == '\v' || c == '\r');
}

int		tkz_is_endcommand(char c)
{
	return (c == '\n' || c == ';');
}

int		tkz_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int		tkz_is_control(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
