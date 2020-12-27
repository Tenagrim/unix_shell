/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:40:09 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/27 21:57:48 by jsandsla         ###   ########.fr       */
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

	int			current_token;
	t_tkz		*tkz;
	int			tkz_error;
}				t_super;

# define SUP_SUCCESS (1)
# define SUP_ERROR (-50)
# define SUP_ERROR_NO_ARGUMENTS (-51)
# define SUP_ERROR_MALLOC_NULL_RETURN (-52)
# define SUP_ERROR_INVALID_REDIRECTION_SYNTAX (-53)
# define SUP_ERROR_MISSING_REDIRECTION_FILE (-54)
# define SUP_ERROR_INVALID_REDIRECTION_FILE (-55)
# define SUP_ERROR_UNRECOGNIZED_REDIRECTION (-56)
# define SUP_ERROR_INVALID_EXEC_SEPARATION (-57)
# define SUP_ERROR_INVALID_PIPE_SYNTAX (-58)

# define SUP_REDIRECTION_IN_FLAG (1 << 0)
# define SUP_REDIRECTION_OUT_FLAG (1 << 1)
# define SUP_REDIRECTION_OUT_APPEND_FLAG (1 << 2)
# define SUP_REDIRECTION_PIPE_FLAG (1 << 3)

t_super		*init_super(void);
void		free_super(t_super **psuper);
int			make_super(t_super *super);

int			is_super_error(int error);
const char	*super_error_str(int error);

void		print_super(t_super *super);

#endif
