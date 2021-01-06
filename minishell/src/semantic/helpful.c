/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpful.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:10:24 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 14:52:10 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

void	sp_memcpy(void *l, void *r, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)l)[i] = ((unsigned char *)r)[i];
		i += 1;
	}
}

int		copy_token_string(t_token *tkn, char **pstr)
{
	if (*pstr)
		free(*pstr);
	(*pstr) = malloc(tkn->len + 1);
	if (!(*pstr))
		return (SUP_ERROR_MALLOC_NULL_RETURN);
	sp_memcpy((*pstr), tkn->mem, tkn->len);
	(*pstr)[tkn->len] = '\0';
	return (SUP_SUCCESS);
}
