/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:14:13 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 21:26:55 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdlib.h>

t_program	*get_current_program(t_super *sp)
{
	t_program	*pr;

	pr = 0;
	if (sp->count > 0)
		pr = &sp->programs[sp->count - 1];
	return (pr);
}

int			expand_super_programs_array(t_super *sp)
{
	int		new_cap;
	void	*new_ptr;

	new_cap = sp->cap * 2;
	if (new_cap <= 0)
		new_cap = 16;
	new_ptr = malloc(sizeof(t_program) * new_cap);
	if (!new_ptr)
		return (SUP_ERROR_MALLOC_NULL_RETURN);
	if (sp->programs)
	{
		sp_memcpy(new_ptr, sp->programs, sizeof(t_program) * sp->count);
		free(sp->programs);
	}
	sp->programs = new_ptr;
	sp->cap = new_cap;
	return (SUP_SUCCESS);
}

void		delete_current_program(t_super *sp)
{
	t_program	*pr;

	pr = get_current_program(sp);
	if (pr)
	{
		free_super_program(pr);
		sp->count -= 1;
	}
}

int			make_super(t_super *sp)
{
	int		error;
	int		state;

	free_super_programs(sp);
	sp->current_token = 0;
	error = tkz_make(sp->tkz);
	if (tkz_is_error(error))
		return (error);
	sp->count += 1;
	init_super_program(get_current_program(sp));
	error = SUP_SUCCESS;
	state = SUP_STATE_ARGUMENT;
	while (!is_super_error(error) && state != SUP_STATE_TERMINATE)
	{
		if (state == SUP_STATE_ARGUMENT)
			error = subprocessor_argument(sp, &state);
		if (state == SUP_STATE_REDIRECT)
			error = subprocessor_redirect(sp, &state);
		if (state == SUP_STATE_PIPE)
			error = subprocessor_pipe(sp, &state);
	}
	if (is_super_error(error) || !get_current_program(sp)->arguments)
		delete_current_program(sp);
	error = rechange_error(sp, error);
	return (error);
}
