#include <minishell.h>

void	free_nullterm_char_arr(char ***arr)
{
	char	**p;

	if (!(*arr))
		return ;
	p = *arr;
	while (*p)
	{
		free(*p);
		p++;
	}
	free(*arr);
	*arr = NULL;
}
