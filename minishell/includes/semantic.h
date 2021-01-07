/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:40:09 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/07 12:41:31 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMANTIC_H
# define SEMANTIC_H

# include "token.h"

typedef struct	t_program
{
	int			arg_cap;
	int			arg_count;
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

	int			current_token;
	t_tkz		*tkz;
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
# define SUP_ERROR_INVALID_SYNTAX (-58)

# define SUP_STATE_ARGUMENT 0
# define SUP_STATE_REDIRECT 1
# define SUP_STATE_PIPE 2
# define SUP_STATE_TERMINATE 3

# define C_LFT_RDR	(1 << 0)
# define C_RT_RDR	(1 << 1)
# define C_RTT_RDR	(1 << 2)
# define C_PIPE		(1 << 3)
# define C_BUILTIN	(1 << 4)

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
