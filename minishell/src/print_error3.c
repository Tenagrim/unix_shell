/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:56:29 by gshona            #+#    #+#             */
/*   Updated: 2021/01/03 14:01:46 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_error3(char  *str1, char *str2, char *error)
{
	write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	write(2, ": ", 2);
	write(2, str2, ft_strlen(str2));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}
