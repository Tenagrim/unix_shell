/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:05:55 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 14:55:15 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdio.h>

void	free_super_program(t_program *pr)
{
	void	*ptr;

	ptr = pr->arguments;
	while (ptr && *pr->arguments)
	{
		free(*pr->arguments);
		pr->arguments += 1;
	}
	if (ptr)
		free(ptr);
	if (pr->redirect_filename[0])
		free(pr->redirect_filename[0]);
	if (pr->redirect_filename[1])
		free(pr->redirect_filename[1]);
}

void	free_super_programs(t_super *sp)
{
	int		i;

	i = 0;
	while (i < sp->count)
	{
		free_super_program(&sp->programs[i]);
		i += 1;
	}
	sp->count = 0;
}

void	free_super(t_super **psp)
{
	if (*psp)
	{
		if ((*psp)->tkz)
			tkz_free(&(*psp)->tkz);
		if ((*psp)->count)
			free_super_programs(*psp);
		if ((*psp)->programs)
			free((*psp)->programs);
		free(*psp);
		*psp = 0;
	}
}
