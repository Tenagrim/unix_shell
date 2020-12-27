
#include "../src/token.h"
#include <stdio.h>

int		main() {
	int		error;
	t_tkz	*tkz = tkz_init();

	error = TKZ_SUCCESS;
	while (!tkz_is_error(error))
	{
		if (tkz_is_error((error = tkz_make(tkz))))
			printf("tkz error: %s\n", tkz_error_str(error));
		else
			tkz_print_lite(tkz);
		printf("\n");
	}

	tkz_free(&tkz);
}



