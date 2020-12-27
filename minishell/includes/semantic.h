/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:40:09 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/27 15:45:54 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMANTIC_H
# define SEMANTIC_H

# include "token.h"

typedef struct	s_program
{
	char		**arguments;
	char		*redirect_filename[2];
	unsigned	flags;
	int			fd[2];
}				t_program;

typedef struct	s_super
{
	int			cap;
	int			count;
	t_program	*programs;
}				t_super;

t_super		*make_super(void);
void		free_super(t_super **psuper);



#endif
