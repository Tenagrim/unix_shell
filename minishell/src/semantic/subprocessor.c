/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprocessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:45:09 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 19:54:20 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int		subprocessor_argument(t_super *sp, int *state)
{
	int			error;
	t_token		*current;

	error = SUP_SUCCESS;
	while (!is_super_error(error) && (current = get_current_token(sp)))
	{
		if (is_token_redirect(current))
			*state = SUP_STATE_REDIRECT;
		else if (is_token_pipe(current))
			*state = SUP_STATE_PIPE;
		else
			error = add_program_argument(get_current_program(sp), current);
		increment_token_pointer(sp);
	}
	if (!current)
		*state = SUP_STATE_TERMINATE;
	return (error);
}

int		subprocessor_redirect(t_super *sp, int *state)
{
	int		error;
	t_token	*current;

	error = SUP_SUCCESS;
	while (!is_super_error(error) && (current = get_current_token(sp)))
	{
		if (token_compare(current, "<", 1))
			error = subprocessor_redirect_input(sp, state);
		else if (token_compare(current, ">", 1))
			error = subprocessor_redirect_output(sp, state);
		else if (token_compare(current, ">>", 2))
			error = subprocessor_redirect_output_append(sp, state);
		else
		{
			*state = SUP_STATE_ARGUMENT;
			break ;
		}
	}
	if (!current)
		*state = SUP_STATE_TERMINATE;
	return (error);
}

int		subprocessor_pipe(t_super *sp, int *state)
{
	int			error;
	t_program	*pr;

	pr = get_current_program(sp);
	pr->flags |= SUP_REDIRECTION_PIPE_FLAG;
	*state = SUP_STATE_ARGUMENT;
	error = SUP_SUCCESS;
	if (sp->count >= sp->cap)
		error = expand_super_programs_array(sp);
	if (!is_super_error(error))
	{
		sp->count += 1;
		init_super_program(get_current_program(sp));
	}
	return (SUP_SUCCESS);
}
