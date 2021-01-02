/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:22:36 by gshona            #+#    #+#             */
/*   Updated: 2021/01/02 22:07:37 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	write_prompt(void)
{
	char	prompt[301];
	char	*prompt_2;
	(void)prompt;

	prompt_2 = "minishell: ";
	write(2, prompt_2, ft_strlen(prompt_2));
//	if (getcwd(prompt, 300))
//		write(2, prompt, ft_strlen(prompt));
//	else
//		write(2, "{long path}", 11);
	write(2, " $ ", 3);
}
