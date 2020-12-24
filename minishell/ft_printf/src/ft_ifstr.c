/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:29:23 by gshona            #+#    #+#             */
/*   Updated: 2020/11/11 17:26:23 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_ifstr(t_attr *attr, va_list arg)
{
	char	*str;
	int		len;

	str = va_arg(arg, char *);
	if (!str)
	{
		str = ft_strdup("(null)");
		len = ft_format_output_str(attr, str);
		free(str);
		return (len);
	}
	if (attr->width < 0)
	{
		attr->width = -attr->width;
		attr->flags = attr->flags & FLAG_MINUS;
	}
	len = ft_format_output_str(attr, str);
	return (len);
}
