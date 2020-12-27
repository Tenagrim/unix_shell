/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:40:09 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/27 17:25:26 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMANTIC_H
# define SEMANTIC_H

# include "token.h"
# define C_LFT_RDR	(1 << 0)
# define C_RT_RDR	(1 << 1)
# define C_RTT_RDR	(1 << 2)
# define C_PIPE		(1 << 3)
# define C_BUILTIN	(1 << 4)

typedef struct	s_program
{
	char		**arguments;
	char		*redirect_filename[2];
	unsigned	flags;
	int			fd[2];
	char		**env;
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
