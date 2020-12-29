/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 12:31:24 by gshona            #+#    #+#             */
/*   Updated: 2020/12/29 17:46:56 by gshona           ###   ########.fr       */
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
int		exec_redirected(int (*exec_func)(const char *path, char *const argv[], char *const envp[]),char *exec_path, char **av, int *fds, char **env);
int		exec_commands(t_super *progs, char **env);
int		exec_command(char **av, char **env);
char	**copy_env(char **env);
int		replace_exec_path(char **value, char **env);
void	free_nullterm_char_arr(char ***arr);
void	print_env_e(char **env);
void	forked_signal_handler(int sig);
void	signal_handler(int sig);
void	write_prompt(void);
void	print_error(char *error);
int		exit_biultin(const char *path, char *const argv[], char *const envp[]);

#endif
