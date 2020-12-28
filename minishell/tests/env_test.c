

#include "../src/env.h"
#include <stdio.h>

int main(int argc, char *argv[], char *native[]) {
	t_env	*env = init_env();

	printf("merge: %d\n", merge_env_native(env, native));
	add_env_variable_expr(env, "H=5", 3);
	add_env_variable_expr(env, "H=2", 3);
	print_env(env);


	free_env(&env);
}
