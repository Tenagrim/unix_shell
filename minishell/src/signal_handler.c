/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:18:23 by gshona            #+#    #+#             */
/*   Updated: 2020/12/29 16:25:46 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_handler(int sig)
{
	if (sig == 2)
	{
		write(2,"\n",1);
		write_prompt();
	}
	else if (sig == 3)
	{
		write(2,"\n", 1);
		write_prompt();
	}
}

void	forked_signal_handler(int sig)
{
	(void)sig;
}
