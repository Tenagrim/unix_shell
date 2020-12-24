#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>

typedef		struct{

}			t_args;


/*
** Returns value from array of env vars by key
** Here is no mallocs
** Don't free or modify return value of this function
** Use strdup if you need this
*/
char	*get_env_value(char **env, char *key);


char	**copy_env(char **env);
void	free_nullterm_char_arr(char ***arr);
void	print_env(char **env);

#endif
