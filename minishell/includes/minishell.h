/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 12:31:24 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 16:55:53 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <semantic.h>
# include <env.h>
# include <exec_args.h>

#include <stdio.h>

/*
** get_env_value
** Returns value from array of env vars by key
** Here is no mallocs
** Don't free or modify return value of this function
** Use strdup if you need this
*/
char	*get_env_value(char **env, char *key);

/*
** find_file_in_dir
** return:	-1 - error (no such directory)
** 			0  - not found
** 			1  - found
*/
int		find_file_in_dir(char *dir_name, char *file);

/*
** find path
** find full path to executable name by $PATH and ex's name
** return must be freed
*/
char	*find_path(char *path, char *name);
int		exec_redirected(t_exec_args *a, t_env *env);
//int		exec_redirected(int (*exec_func)(char *const argv[], t_env *env),char *exec_path, char **av, int *fds, t_env *env);
int		exec_commands(t_super *progs, t_env *env);
int		exec_command(char **av, char **env);
char	**copy_env(char **env);
int		replace_exec_path(char **value, t_env *env);
void	free_nullterm_char_arr(char ***arr);
void	print_env_e(char **env);
void	forked_signal_handler(int sig);
void	signal_handler(int sig);
void	write_prompt(void);
void	print_error(char *error);
int		exit_biultin(char *const argv[], t_env *env);
int		is_dir(char *name);
int		pwd_biultin(char *const argv[], t_env *env);
int		export_biultin(char *const argv[], t_env *env);
int		unset_biultin(char *const argv[], t_env *env);
int		pwd_biultin(char *const argv[], t_env *env);
int		env_biultin(char *const argv[], t_env *env);
int		cd_biultin(char *const argv[], t_env *env);
int		echo_biultin(char *const argv[], t_env *env);
int		exit_biultin(char *const argv[], t_env *env);
void	print_error1(char *error);
void	print_error2(char *error, char  *str);
void	print_error3(char  *str1, char *str2, char *error);
int		(*get_exec_func(char *name))(char *const argv[], t_env *env);

#endif
