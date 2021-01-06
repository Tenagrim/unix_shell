/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:14:03 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 21:27:17 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_H
# define PRIVATE_H

# include <semantic.h>

void		print_super(t_super *sp);

int			expand_program_argument_array(t_program *pr);
int			add_program_argument(t_program *pr, t_token *token);

int			is_token_redirect(t_token *tkn);
int			is_token_pipe(t_token *tkn);
int			is_token_argument(t_token *tkn);

int			is_super_error(int error);
const char	*super_error_str(int error);
int			rechange_error(t_super *sp, int error);

void		free_super_program(t_program *pr);
void		free_super_programs(t_super *sp);
void		free_super(t_super **psp);

void		sp_memcpy(void *l, void *r, int len);
int			copy_token_string(t_token *tkn, char **pstr);

t_super		*init_super(void);
void		init_super_program(t_program *pr);

t_token		*get_current_token(t_super *sp);
t_token		*get_offseted_token(t_super *sp, int offset);
void		increment_token_pointer(t_super *sp);
void		move_token_pointer(t_super *sp, int offset);
int			token_compare(t_token *tkn, const char *str, int len);

int			subprocessor_redirect_input(t_super *sp, int *state);
int			subprocessor_redirect_output(t_super *sp, int *state);
int			subprocessor_redirect_output_append(t_super *sp, int *state);

int			subprocessor_argument(t_super *sp, int *state);
int			subprocessor_redirect(t_super *sp, int *state);
int			subprocessor_pipe(t_super *sp, int *state);

t_program	*get_current_program(t_super *sp);
int			expand_super_programs_array(t_super *sp);
void		delete_last_program(t_super *sp);
int			make_super(t_super *sp);

#endif
