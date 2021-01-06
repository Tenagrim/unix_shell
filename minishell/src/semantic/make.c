/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:14:13 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 14:58:41 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int		make_super_token(t_super *sp)
{
	int		error;

	free_super_programs(sp);
	sp->current_token = 0;
	error = tkz_make(sp->tkz);
	sp->tkz_error = error;
	return (error);
}

int		make_super(t_super *sp)
{
	int		error;
	int		remains;
	t_token	*tkn;

	error = make_super_token(sp);
	if (tkz_is_error(error))
		return (error);
	if (is_super_error((error = make_super_program(sp,
			&sp->programs[sp->count++], &remains))))
		delete_last_program(sp);
	while (!is_super_error(error) && remains)
	{
		tkn = get_current_token(sp);
		if (!is_token_pipe(tkn))
			return (SUP_ERROR_INVALID_EXEC_SEPARATION);
		increment_token_pointer(sp);
		if (sp->count >= sp->cap)
			error = expand_super_programs_array(sp);
		if (!is_super_error(error))
			error = make_super_program(sp,
				&sp->programs[sp->count++], &remains);
	}
	error = rechange_error(sp, remains, error);
	return (error);
}
