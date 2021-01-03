/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 16:49:03 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 16:50:24 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_ARGS_H
# define EXEC_ARGS_H
# include <env.h>

typedef struct s_exec_args
{
	int			**pipes;
	int			cur_pipe;
	t_program	*prog;
	int			inp_fd;
	int			fds[2];
	char		*exec_path;
	int			(*exec_func)(char *const argv[], t_env *env);
}				t_exec_args;
#endif
