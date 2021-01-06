/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:04:37 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 21:07:33 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdlib.h>

t_super	*init_super(void)
{
	t_super	*super;

	super = malloc(sizeof(t_super));
	if (super)
	{
		super->cap = 16;
		super->count = 0;
		super->programs = malloc(sizeof(t_program) * super->cap);
		if (super->programs)
		{
			super->tkz = tkz_init();
			super->current_token = 0;
			if (!super->tkz)
				free_super(&super);
		}
		else
			free_super(&super);
	}
	return (super);
}

void	init_super_program(t_program *pr)
{
	pr->arg_cap = 0;
	pr->arg_count = 0;
	pr->arguments = 0;
	pr->redirect_filename[0] = 0;
	pr->redirect_filename[1] = 0;
	pr->flags = 0;
	pr->fd[0] = 0;
	pr->fd[1] = 1;
}
