/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:27:01 by gshona            #+#    #+#             */
/*   Updated: 2020/11/01 13:04:10 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	half(char **format, int *res)
{
	int	passed;

	passed = 0;
	if (format[0][0] == 'l' && format[0][1] == 'l')
	{
		*res = *res | SIZE_LL;
		*format = *format + 2;
		passed = 1;
	}
	else if (format[0][0] == 'l')
	{
		*res = *res | SIZE_L;
		*format = *format + 1;
		passed = 1;
	}
	return (passed);
}

int			ft_get_size(char **format)
{
	int	res;

	res = 0;
	if (!ft_strchr(SIZES, **format))
		return (0);
	if (half(format, &res))
		return (res);
	else if (format[0][0] == 'h' && format[0][1] == 'h')
	{
		res = res | SIZE_HH;
		*format = *format + 2;
	}
	else if (format[0][0] == 'h')
	{
		res = res | SIZE_H;
		*format = *format + 1;
	}
	else if (format[0][0] == 'L')
	{
		res = res | SIZE_UP_L;
		*format = *format + 1;
	}
	return (res);
}
