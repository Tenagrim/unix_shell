/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:13:09 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 14:52:42 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int		recognize_program_redirection(t_program *pr, t_token *rd, t_token *fn)
{
	int		error;

	if (token_compare(rd, "<", 1))
	{
		pr->flags |= SUP_REDIRECTION_IN_FLAG;
		error = copy_token_string(fn, &pr->redirect_filename[0]);
	}
	else if (token_compare(rd, ">", 1))
	{
		pr->flags |= SUP_REDIRECTION_OUT_FLAG;
		pr->flags &= ~SUP_REDIRECTION_OUT_APPEND_FLAG;
		error = copy_token_string(fn, &pr->redirect_filename[1]);
	}
	else if (token_compare(rd, ">>", 2))
	{
		pr->flags |= SUP_REDIRECTION_OUT_APPEND_FLAG;
		pr->flags &= ~SUP_REDIRECTION_OUT_FLAG;
		error = copy_token_string(fn, &pr->redirect_filename[1]);
	}
	else
		error = SUP_ERROR_UNRECOGNIZED_REDIRECTION;
	return (error);
}

int		make_super_program(t_super *sp, t_program *pr, int *remains)
{
	int		error;
	t_token	*tkn;
	t_token	*tkn_n;

	init_super_program(pr);
	error = make_super_program_arguments(sp, pr);
	while ((tkn = get_current_token(sp)) && !is_super_error(error) &&
		!is_token_pipe(tkn))
	{
		if (!is_token_redirect(tkn))
			return (SUP_ERROR_INVALID_REDIRECTION_SYNTAX);
		increment_token_pointer(sp);
		tkn_n = get_current_token(sp);
		if (!tkn_n)
			return (SUP_ERROR_MISSING_REDIRECTION_FILE);
		if (!is_token_argument(tkn_n))
			return (SUP_ERROR_INVALID_REDIRECTION_FILE);
		increment_token_pointer(sp);
		error = recognize_program_redirection(pr, tkn, tkn_n);
	}
	if (!is_super_error(error) && tkn && is_token_pipe(tkn))
		pr->flags |= SUP_REDIRECTION_PIPE_FLAG;
	*remains = !!tkn;
	return (error);
}

int		expand_super_programs_array(t_super *sp)
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

void	delete_last_program(t_super *sp)
{
	if (sp->count - 1 >= 0)
	{
		free_super_program(&sp->programs[sp->count - 1]);
		sp->count -= 1;
	}
}
