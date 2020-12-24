/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:12:53 by gshona            #+#    #+#             */
/*   Updated: 2020/11/11 18:15:51 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

size_t		ft_str_len(char *str)
{
	size_t	res;

	res = 0;
	while (*str)
	{
		if (*str != '-')
			res++;
		str += 1;
	}
	return (res);
}