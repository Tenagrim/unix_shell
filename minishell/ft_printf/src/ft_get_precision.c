/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:26:33 by gshona            #+#    #+#             */
/*   Updated: 2020/11/11 18:10:41 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		support(char **format, int *len, char *start)
{
	while (ft_isdigit(**format))
		*format = *format + 1;
	*len = format[0] - start;
}

static int		support_two(char *start, int len)
{
	char	*digit;
	int		res;

	digit = ft_substr(start, 0, len);
	res = ft_atoi(digit);
	free(digit);
	return (res);
}

int				ft_get_precision(char **format, va_list arg)
{
	char	*start;
	int		len;
	int		tmp;

	if (**format == '.')
		*format = *format + 1;
	else
		return (-1);
	if (**format == '*')
	{
		*format = *format + 1;
		tmp = va_arg(arg, int);
		return (tmp);
	}
	start = *format;
	support(format, &len, start);
	if (len == 0)
		return (0);
	else
	{
		return (support_two(start, len));
	}
}
