/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 12:11:05 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/03 11:48:07 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

typedef struct	s_token
{
	int		cap;
	int		len;
	char	*mem;
}				t_token;

typedef struct s_tokenizer_buffer
{
	int			fd;
	int			start;
	int			len;
	char		mem[BUFFER_SIZE];
}				t_tkz_buf;

# define STATE_NORMAL 0
# define STATE_QUOTE 1
# define STATE_DQUOTE 2
# define STATE_TERMINATE 3

typedef int		(*t_tkz_env_get)(void *data, char *name, char **value);
typedef int		(*t_tkz_last_exit_code)(void *data, int *exit_code);

typedef struct	s_tokenizer
{
	int			tkn_cap;
	int			tkn_count;
	t_token		*tkn;

	unsigned	state;
	int			flags;

	t_tkz_buf	buf;

	void					*data;
	t_tkz_env_get			env_get;
	t_tkz_last_exit_code	last_exit_code;
}				t_tkz;

# define TKZ_FLAG_UNEXPECTED_EOF (1 << 0)
# define TKZ_FLAG_WS_AT_START (1 << 1)

# define TKZ_SUCCESS (1)
# define TKZ_ERROR (-1)
# define TKZ_ERROR_PREFETCH_REQUEST_OVERFLOW (-2)
# define TKZ_ERROR_UNISTD_READ_NEGATIVE_RETURN (-3)
# define TKZ_ERROR_UNISTD_READ_EOF (-4)
# define TKZ_ERROR_MALLOC_NULL_RETURN (-5)
# define TKZ_ERROR_INVALID_DOLLAR_SYNTAX (-6)

/*
** internal errors (indicates bugs in library)
*/
# define TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_NORMAL_ESCAPE (-20)
# define TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_BACKSLASH_DQUOTE_ESCAPE (-21)
# define TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DOLLAR_SYMBOL (-22)
# define TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_QUATION_MARK_SYMBOL (-23)
# define TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_CONTROL_CHARACTER (-24)
# define TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_QUOTE_SYMBOL (-25)
# define TKZ_ERROR_CONTRACT_IS_TERMINATED_FOR_DQUOTE_SYMBOL (-26)

t_tkz			*tkz_init(void);
void			tkz_change_input_fd(t_tkz *tkz, int fd);
int				tkz_make(t_tkz *tkz);
void			tkz_free(t_tkz **tkz);

int				tkz_is_command_buffered(t_tkz *tkz);
int				tkz_check_flag(t_tkz *tkz, int flag);

int				tkz_is_error(int value);
const char		*tkz_error_str(int value);

void			tkz_print(t_tkz *tkz);
void			tkz_print_lite(t_tkz *tkz);

#endif
