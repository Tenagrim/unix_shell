/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:22:36 by gshona            #+#    #+#             */
/*   Updated: 2020/12/29 14:23:16 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	write_prompt(void)
{
	char	prompt[301];
	char	*prompt_2;

	prompt_2 = "minishell: ";
	write(2, prompt_2, ft_strlen(prompt_2));
	if (getcwd(prompt, 300))
		write(2, prompt, ft_strlen(prompt));
	else
		write(2, "{long path}", 11);
	write(2, " $ ", 3);
}
