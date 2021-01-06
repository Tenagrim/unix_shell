/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:11:41 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 17:00:31 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdlib.h>

int		count_super_program_arguments(t_super *sp)
{
	int		count;
	t_token	*tkn;

	count = 0;
	while ((tkn = get_current_token(sp)))
	{
		if (is_token_argument(tkn))
			count += 1;
		else
			break ;
		increment_token_pointer(sp);
	}
	move_token_pointer(sp, -count);
	return (count);
}

int		make_super_program_arguments(t_super *sp, t_program *pr)
{
	int		count;
	int		error;
	t_token	*tkn;
	int		i;

	count = count_super_program_arguments(sp);
	if (!count)
		return (SUP_ERROR_NO_ARGUMENTS);
	pr->arguments = malloc(sizeof(char *) * (count + 1));
	if (!pr->arguments)
		return (SUP_ERROR_MALLOC_NULL_RETURN);
	error = SUP_SUCCESS;
	i = 0;
	while (!is_super_error(error) && i < count)
	{
		tkn = get_offseted_token(sp, i);
		pr->arguments[i] = 0;
		error = copy_token_string(tkn, &pr->arguments[i]);
		i += 1;
	}
	pr->arguments[i] = 0;
	move_token_pointer(sp, count);
	return (error);
}
