/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:22:18 by gshona            #+#    #+#             */
/*   Updated: 2020/12/24 13:16:05 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_loop()
{
	

}


int		main(int ac, char **av, char **env)
{
	char	**tmp;

	tmp = copy_env(env);
	ft_printf("%d %s %s\n", ac, av[0], env[0]);
	print_env(tmp);
	free_nullterm_char_arr(&tmp);
	ft_printf( "hello world");

	ft_printf(">>> |%s|\n", get_env_value(env,"TERM_PROGRAMa"));


}
