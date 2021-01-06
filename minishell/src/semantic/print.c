/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:14:39 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 15:01:09 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdio.h>

void	print_program(t_program *pr)
{
	int		j;

	printf(" - args:");
	j = 0;
	while (pr->arguments && pr->arguments[j])
	{
		printf(" %s", pr->arguments[j]);
		j += 1;
	}
	printf("\n - redirect[0]: %s\n - redirect[1]: %s\n",
		pr->redirect_filename[0],
		pr->redirect_filename[1]);
	printf(" - flags:");
	if (pr->flags & SUP_REDIRECTION_IN_FLAG)
		printf(" IN");
	if (pr->flags & SUP_REDIRECTION_OUT_FLAG)
		printf(" OUT");
	if (pr->flags & SUP_REDIRECTION_OUT_APPEND_FLAG)
		printf(" OUT_APPEND");
	if (pr->flags & SUP_REDIRECTION_PIPE_FLAG)
		printf(" PIPE");
}

void	print_super(t_super *sp)
{
	int		i;

	i = 0;
	while (i < sp->count)
	{
		printf("program[%d]\n", i);
		print_program(&sp->programs[i]);
		printf("\n");
		i += 1;
	}
}
