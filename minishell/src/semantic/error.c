/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:07:05 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 21:01:12 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int			is_super_error(int error)
{
	return (error != SUP_SUCCESS);
}

const char	*super_error_str(int error)
{
	if (error == SUP_ERROR)
		return ("unrecognized error");
	else if (error == SUP_ERROR_NO_ARGUMENTS)
		return ("no arguments");
	else if (error == SUP_ERROR_MALLOC_NULL_RETURN)
		return ("malloc null return");
	else if (error == SUP_ERROR_INVALID_REDIRECTION_SYNTAX)
		return ("invalid redirection syntax");
	else if (error == SUP_ERROR_MISSING_REDIRECTION_FILE)
		return ("missing redirection file");
	else if (error == SUP_ERROR_INVALID_REDIRECTION_FILE)
		return ("invalid redirection file");
	else if (error == SUP_ERROR_UNRECOGNIZED_REDIRECTION)
		return ("unrecognized redirection");
	else if (error == SUP_ERROR_INVALID_EXEC_SEPARATION)
		return ("invalid exec separation");
	else if (error == SUP_ERROR_INVALID_SYNTAX)
		return ("invalid syntax");
	else
		return (tkz_error_str(error));
}

int			rechange_error(t_super *sp, int error)
{
	if (error == SUP_ERROR_NO_ARGUMENTS && (sp->count > 0))
		error = SUP_ERROR_INVALID_SYNTAX;
	return (error);
}
