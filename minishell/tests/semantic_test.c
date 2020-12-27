

#include "../src/semantic.h"
#include <stdio.h>
#include <stdlib.h>

int		main() {
	t_super	*sp;
	int		error;

	sp = init_super();
	if (!sp)
		exit(1);

	while (!is_super_error((error = make_super(sp)))) {
		print_super(sp);
	}

	if (is_super_error(error))
		printf("error: %s\n", super_error_str(error));

	free_super(&sp);
}
