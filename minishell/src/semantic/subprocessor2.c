/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprocessor2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:13:09 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 21:25:44 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <fcntl.h>

void	create_file(const char *filename, int flags)
{
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | flags, 0644);
	if (fd >= 0)
		close(fd);
}

int		subprocessor_redirect_input(t_super *sp, int *state)
{
	t_token		*current;
	t_program	*program;
	int			error;

	(void)state;
	increment_token_pointer(sp);
	current = get_current_token(sp);
	if (!current || !is_token_argument(current))
		return (SUP_ERROR_MISSING_REDIRECTION_FILE);
	program = get_current_program(sp);
	program->flags |= SUP_REDIRECTION_IN_FLAG;
	error = copy_token_string(current, &program->redirect_filename[0]);
	increment_token_pointer(sp);
	return (error);
}

int		subprocessor_redirect_output(t_super *sp, int *state)
{
	t_token		*current;
	t_program	*program;
	int			error;

	(void)state;
	increment_token_pointer(sp);
	current = get_current_token(sp);
	if (!current || !is_token_argument(current))
		return (SUP_ERROR_MISSING_REDIRECTION_FILE);
	program = &sp->programs[sp->count - 1];
	program->flags |= SUP_REDIRECTION_OUT_FLAG;
	program->flags &= ~SUP_REDIRECTION_OUT_APPEND_FLAG;
	if (program->redirect_filename[1])
		create_file(program->redirect_filename[1], O_TRUNC);
	error = copy_token_string(current, &program->redirect_filename[1]);
	increment_token_pointer(sp);
	return (error);
}

int		subprocessor_redirect_output_append(t_super *sp, int *state)
{
	t_token		*current;
	t_program	*program;
	int			error;

	(void)state;
	increment_token_pointer(sp);
	current = get_current_token(sp);
	if (!current || !is_token_argument(current))
		return (SUP_ERROR_MISSING_REDIRECTION_FILE);
	program = &sp->programs[sp->count - 1];
	program->flags |= SUP_REDIRECTION_OUT_APPEND_FLAG;
	program->flags &= ~SUP_REDIRECTION_OUT_FLAG;
	if (program->redirect_filename[1])
		create_file(program->redirect_filename[1], O_APPEND);
	error = copy_token_string(current, &program->redirect_filename[1]);
	increment_token_pointer(sp);
	return (error);
}
