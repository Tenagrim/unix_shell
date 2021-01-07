/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:22:36 by gshona            #+#    #+#             */
/*   Updated: 2021/01/07 14:51:24 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	write_prompt(void)
{
	char	prompt[301];
	char	*prompt_2;

	(void)prompt;
	prompt_2 = "minishell";
	write(2, prompt_2, ft_strlen(prompt_2));
	write(2, "$ ", 2);
}
