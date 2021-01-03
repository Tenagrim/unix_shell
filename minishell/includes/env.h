

#ifndef ENV_H
# define ENV_H

typedef	struct	s_entry {
	int		key_len;
	int		value_len;
	char	*key;
	char	*value;
}				t_var;

typedef struct	s_environment {
	int				var_cap;
	int				var_count;
	unsigned char	last_code;
	t_var			*var;

}				t_env;

t_env	*init_env(void);
void	free_env(t_env **penv);

int		add_env_variable(t_env *env, char *key, int klen, char *value, int vlen);
int		add_env_variable_expr(t_env *env, char *expr, int len);
void	remove_env_variable(t_env *env, char *key, int klen);
int		find_env_variable(t_env *env, char *key, int klen);
int		find_env_variable_cb(t_env *env, char *key, char **value_canbenull);
int		find_env_variable_cb_static(t_env *env, char *key, char **value_canbenull);
int		get_last_code(void *data, int *exit_code);

char	**gen_native_env(t_env *env);
void	free_env_native(char **native);
int		merge_env_native(t_env *env, char **native);

void	print_env(t_env *env);

#endif
