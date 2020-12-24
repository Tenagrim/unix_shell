/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:27:23 by gshona            #+#    #+#             */
/*   Updated: 2020/11/11 18:06:36 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	star_procession(va_list arg)
{
	int tmp;

	tmp = va_arg(arg, int);
	return (tmp);
}

int			ft_get_width(char **format, va_list arg, t_attr *attr)
{
	int		res;
	char	*start;
	char	*digit;
	int		len;

	start = *format;
	if (**format == '*')
	{
		*format = *format + 1;
		return (star_procession(arg));
	}
	while (ft_isdigit(**format))
		*format = *format + 1;
	len = format[0] - start;
	if (len == 0)
		return (0);
	else
	{
		digit = ft_substr(start, 0, len);
		attr->unset_wid = 0;
		res = ft_atoi(digit);
		free(digit);
		return (res);
	}
}
