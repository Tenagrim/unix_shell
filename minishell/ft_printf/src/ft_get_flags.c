/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:26:18 by gshona            #+#    #+#             */
/*   Updated: 2020/11/01 17:14:11 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_get_flags(char **format)
{
	int res;

	res = 0;
	while (ft_strchr(FLAGS, **format))
	{
		if (**format == '+')
			res = res | FLAG_PLUS;
		else if (**format == '-')
			res = res | FLAG_MINUS;
		else if (**format == '#')
			res = res | FLAG_SHARP;
		else if (**format == '0')
			res = res | FLAG_ZERO;
		else if (**format == ' ')
			res = res | FLAG_SPACE;
		*format = *format + 1;
	}
	return (res);
}
