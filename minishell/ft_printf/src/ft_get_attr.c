/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_attr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:25:56 by gshona            #+#    #+#             */
/*   Updated: 2020/11/11 17:29:17 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

t_attr	*ft_get_attr(char **format, va_list arg)
{
	t_attr	*res;

	res = ft_new_attr();
	res->wid = 0;
	res->unset_wid = 1;
	res->flags = ft_get_flags(format);
	res->width = ft_get_width(format, arg, res);
	res->precision = ft_get_precision(format, arg);
	res->flags = res->flags | ft_get_size(format);
	res->conv = ft_get_conv(format);
	if (res->width < 0)
	{
		res->width = -res->width;
		res->flags = res->flags | FLAG_MINUS;
	}
	return (res);
}
