/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:53:06 by jsandsla          #+#    #+#             */
/*   Updated: 2021/01/06 16:56:04 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_H
# define PRIVATE_H

# include <env.h>

int		find_env_variable(t_env *env, char *key);
int		find_env_variable_cb(t_env *env, char *key, char **value_canbenull);
int		find_env_variable_cb_static(t_env *env, char *key,
	char **value_canbenull);

void	free_env(t_env **penv);
void	free_env_vars(t_env *env);
void	free_env_var(t_var *var);
void	free_env_native(char **native);

int		copy_string(char *str, char **out, int *out_len_canbenull);
int		string_eq(char *l, char *r);
void	env_memcpy(void *l, void *r, int len);

void	init_env_var(t_var *var);
t_env	*init_env(void);

char	*gen_var_expr(t_var *var);
char	**gen_native_env(t_env *env);
int		merge_env_native(t_env *env, char **native);

void	print_env(t_env *env);

int		expand_env_variables_array(t_env *env);
int		get_variable(t_env *env, char *key);
int		add_env_variable(t_env *env, char *key, char *value);
int		add_env_variable_expr(t_env *env, char *expr);
void	remove_env_variable(t_env *env, char *key);

#endif
