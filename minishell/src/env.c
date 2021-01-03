
#include "env.h"
#include <string.h>
#include <stdlib.h>

void	free_env_var(t_var *var) {
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	var->key = 0;
	var->value = 0;
	var->key_len = 0;
	var->value_len = 0;
}

void	free_env_vars(t_env *env) {
	int		i;

	i = 0;
	while (i < env->var_count) {
		free_env_var(&env->var[i]);
		i += 1;
	}
}

void	free_env(t_env **penv) {
	if (*penv) {
		if ((*penv)->var_count)
			free_env_vars(*penv);
		if ((*penv)->var)
			free((*penv)->var);
		free(*penv);
		*penv = 0;
	}
}

t_env	*init_env(void) {
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env) {
		env->last_code = 0;
		env->var_cap = 16;
		env->var_count = 0;
		env->var = malloc(sizeof(t_var) * env->var_cap);
		if (!env->var)
			free_env(&env);
	}
	return (env);
}

void	init_env_var(t_var *var) {
	var->key_len = 0;
	var->key = 0;
	var->value_len = 0;
	var->value = 0;
}

int		copy_string(char *str, char **out, int *out_len_canbenull) {
	int		success;
	int		len;
	int		i;

	success = 0;
	if (str) {
		len = 0;
		while (str[len]) {
			len += 1;
		}
		*out = malloc(len + 1);
		if (*out) {
			i = 0;
			while (i < len) {
				(*out)[i] = str[i];
				i += 1;
			}
			(*out)[i] = 0;
			if (out_len_canbenull)
				*out_len_canbenull = len;
			success = 1;
		}
	}
	return (success);
}

int		expand_env_variables_array(t_env *env) {
	int		success;
	int		new_cap;
	void	*new_ptr;

	success = 0;
	new_cap = env->var_cap * 2;
	if (new_cap <= 0)
		new_cap = 16;
	new_ptr = malloc(new_cap * sizeof(t_var));
	if (new_ptr) {
		if (env->var) {
			memcpy(new_ptr, env->var, env->var_count * sizeof(t_var));
			free(env->var);
		}
		env->var = new_ptr;
		env->var_cap = new_cap;
		success = 1;
	}
	return (success);
}

int		get_variable(t_env *env, char *key) {
	int		i;
	int		success;

	success = 1;
	i = find_env_variable(env, key);
	//printf("k:%.*s[%d]\n", klen, key, i);
	if (i < 0) {
		if (env->var_count >= env->var_cap) {
			success = expand_env_variables_array(env);
		}
		if (success) {
			i = env->var_count++;
			init_env_var(&env->var[i]);
		}
	}
	return (success ? i : -1);
}

int		add_env_variable(t_env *env, char *key, char *value) {
	int		success;
	t_var	*var;
	int		i;

	success = 1;
	if (env->var_count >= env->var_cap) {
		success = expand_env_variables_array(env);
	}
	if (success) {
		i = get_variable(env, key);
		success = 0;
		if (i >= 0) {
			var = &env->var[i];
			if (var->key || var->value)
				free_env_var(var);
			success = copy_string(key, &var->key, &var->key_len);
			if (success) {
				success = copy_string(value, &var->value, &var->value_len);
			}
			if (!success) {
				free_env_var(var);
				env->var_count -= 1;
			}
		}
	}
	return (success);
}

int		add_env_variable_expr(t_env *env, char *expr) {
	int		key_len;
	char	*key;
	int		success;

	success = 0;
	key_len = 0;
	while (expr[key_len] && expr[key_len] != '=') {
		key_len += 1;
	}
	if (expr[key_len] == '=') {
		key = malloc(key_len + 1);
		if (key) {
			memcpy(key, expr, key_len);
			key[key_len] = 0;
			success = add_env_variable(env, key, expr + key_len + 1);
		}
	}
	return (success);
}

int		string_eq(char *l, char *r) {
	while (*l && *l == *r) {
		l += 1;
		r += 1;
	}
	return (*l == *r);
}

void	remove_env_variable(t_env *env, char *key) {
	int		i;

	i = 0;
	while (i < env->var_count) {
		if (string_eq(env->var[i].key, key)) {
			break ;
		}
		i += 1;
	}
	if (i < env->var_count) {
		free_env_var(&env->var[i]);
		memcpy(&env->var[i], &env->var[i + 1], (env->var_count - i - 1) * sizeof(t_var));
		env->var_count -= 1;
	}
}

int		find_env_variable(t_env *env, char *key) {
	int		i;
	t_var	*var;
	int		success;

	success = 0;
	i = 0;
	while (i < env->var_count) {
		var = &env->var[i];
		if (string_eq(key, var->key)) {
			break ;
		}
		i += 1;
	}
	return (i < env->var_count ? i : -1);
}

int		find_env_variable_cb(t_env *env, char *key, char **value_canbenull) {
	int		i;
	t_var	*var;
	int		success;

	success = 0;
	i = find_env_variable(env, key);
	if (i >= 0) {
		var = &env->var[i];
		if (value_canbenull) {
			if (copy_string(var->value, value_canbenull, 0)) {
				success = 1;
			}
		} else {
			success = 1;
		}
	}
	return (success);
}

int		find_env_variable_cb_static(t_env *env, char *key, char **value_canbenull) {
	int		i;
	t_var	*var;
	int		success;

	success = 0;
	i = find_env_variable(env, key);
	if (i >= 0) {
		var = &env->var[i];
		if (value_canbenull) {
			*value_canbenull = var->value;
			success = 1;
		} else {
			success = 1;
		}
	}
	return (success);
}

char	*gen_var_expr(t_var *var) {
	char	*expr;

	expr = malloc(var->key_len + var->value_len + 2);
	if (expr) {
		memcpy(expr, var->key, var->key_len);
		expr[var->key_len] = '=';
		memcpy(expr + var->key_len + 1, var->value, var->value_len);
		expr[var->key_len + 1 + var->value_len] = 0;
	}
	return (expr);
}

char	**gen_native_env(t_env *env) {
	char	**native;
	t_var	*var;
	int		i;

	native = malloc(sizeof(char *) * (env->var_count + 1));
	if (!native)
		return (0);
	i = 0;
	while (i < env->var_count) {
		var = &env->var[i];
		native[i] = gen_var_expr(var);
		if (!native[i])
			break ;
		i += 1;
	}
	native[i] = 0;
	return (native);
}

void	free_env_native(char **native) {
	void	*start;

	if (native) {
		start = native;
		while (*native) {
			free(*native);
			native += 1;
		}
		free(start);
	}
}

int		merge_env_native(t_env *env, char **native) {
	while (*native) {
		if (!add_env_variable_expr(env, *native))
			break ;
		native += 1;
	}
	return (!*native);
}

#include <stdio.h>
#include <unistd.h>

void	print_env(t_env *env) {
	int		i;
	t_var	*var;
	char	buf[1024];

	i = 0;
	while (i < env->var_count) {
		var = &env->var[i];
		int ret = snprintf(buf, sizeof(buf) - 1,"%.*s=%.*s\n", var->key_len, var->key, var->value_len, var->value);
		buf[ret] = 0;
		write(1, buf, ret);
		i += 1;
	}
}

