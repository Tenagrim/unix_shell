/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:11:41 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 19:48:10 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdlib.h>

int		expand_program_argument_array(t_program *pr)
{
	int		new_cap;
	void	*new_mem;

	new_cap = pr->arg_cap * 2;
	if (new_cap <= 0)
		new_cap = 16;
	new_mem = malloc((new_cap + 1) * sizeof (char *));
	if (!new_mem)
		return (SUP_ERROR_MALLOC_NULL_RETURN);
	if (pr->arguments)
	{
		sp_memcpy(new_mem, pr->arguments, (pr->arg_count + 1) * sizeof (char *));
		free(pr->arguments);
	}
	pr->arguments = (char **)new_mem;
	pr->arg_cap = new_cap;
	return (SUP_SUCCESS);
}

int		add_program_argument(t_program *pr, t_token *token)
{
	int		error;

	error = SUP_SUCCESS;
	if (pr->arg_count >= pr->arg_cap)
		error = expand_program_argument_array(pr);
	if (!is_super_error(error))
	{
		error = copy_token_string(token, &pr->arguments[pr->arg_count]);
		if (!is_super_error(error))
		{
			pr->arg_count += 1;
			pr->arguments[pr->arg_count] = 0;
		}
	}
	return (error);
}
