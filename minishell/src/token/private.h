/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:30:26 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 13:56:22 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_H
# define PRIVATE_H

# include <token.h>

int			tkz_buf_init(t_tkz_buf *buf, int fd);
t_tkz		*tkz_init(void);
void		tkz_init_token(t_token *tkn);
void		tkz_change_input_fd(t_tkz *tkz, int fd);
int			tkz_check_flags(t_tkz *tkz, int flags);

int			tkz_buffer_expand(t_tkz_buf *buf, int at_least);
int			tkz_write_buffer_str(t_tkz_buf *buf, const char *str, int len);
int			tkz_buffer_read_command(t_tkz *tkz, t_tkz_buf *buf);
int			tkz_read_buffer(t_tkz_buf *buf);

void		tkz_buffer_increment(t_tkz_buf *buf, int count);
char		tkz_buffer_view_char(t_tkz_buf *buf, int offset);
char		*tkz_buffer_view(t_tkz_buf *buf, int offset);
int			tkz_is_buffer_closed(t_tkz_buf *buf);

void		tkz_buffer_skip_whitespaces(t_tkz_buf *buf);
int			tkz_buffer_is_endcommand(t_tkz_buf *buf);
void		tkz_buffer_full_skip_endcommand(t_tkz_buf *buf);
int			tkz_is_command_buffered(t_tkz *tkz);

int			tkz_is_wp(char c);
int			tkz_is_endcommand(char c);
int			tkz_is_quote(char c);
int			tkz_is_control(char c);

int			tkz_is_word(char c);
int			tkz_is_identifier(char c, int is_begin);

int			tkz_is_error(int error);
const char	*tkz_error_str(int error);

void		tkz_free_buf(t_tkz_buf *buf);
void		tkz_free_tokens(t_tkz *tkz);
void		tkz_free(t_tkz **tkz);
void		tkz_free_token(t_token *tkn);

void		tkz_memcpy(void *l, void *r, int size);
int			tkz_strlen(char *str);
void		tkz_reverse_str(char *begin, int len);
int			tkz_draw_int(char *out, int num);
int			tkz_strchr(char c, const char *str);

int			tkz_make_token(t_tkz *tkz, int i_tkn, int *remains);
int			tkz_make(t_tkz *tkz);

int			tkz_processor_normal(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf);
int			tkz_processor_quote(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf);
int			tkz_processor_dquote(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf);

void		tkz_update_state(t_tkz *tkz, t_tkz_buf *buf);

int			tkz_subprocessor_exit_code(t_tkz *tkz, t_token *tkn,
	t_tkz_buf *buf);
t_token		tkz_subprocessor_env_get_identifier(t_tkz_buf *buf);
int			tkz_subprocessor_env(t_tkz *tkz, t_tkz_buf *buf);
int			tkz_subprocessor_dollar(t_tkz *tkz, t_token *tkn, t_tkz_buf *buf);
int			tkz_subprocessor_normal_escape(t_tkz *tkz, t_token *tkn,
	t_tkz_buf *buf);

int			tkz_subprocessor_dquote_escape(t_tkz *tkz, t_token *tkn,
	t_tkz_buf *buf);
int			tkz_subprocessor_control(t_tkz *tkz, t_token *tkn,
	t_tkz_buf *buf);
int			tkz_subprocessor_dquote_end(t_tkz *tkz, t_token *tkn,
	t_tkz_buf *buf);

int			tkz_expand_tokens_array(t_tkz *tkz);
int			tkz_expand_token_memory(t_token *tkn, int min);
int			tkz_write_token_str(t_token *tkn, char *str, int len);
int			tkz_token_move_char_from_buffer(t_token *tkn, t_tkz_buf *buf);

void		tkz_print_buf(t_tkz_buf *buf);
void		tkz_print_token(t_token *tkn);
void		tkz_print(t_tkz *tkz);
void		tkz_print_lite(t_tkz *tkz);

#endif
