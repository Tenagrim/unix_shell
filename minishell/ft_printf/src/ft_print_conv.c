/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_conv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:33:19 by gshona            #+#    #+#             */
/*   Updated: 2020/11/09 19:18:59 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	abort_(t_attr **attr)
{
	if (*attr)
		free(*attr);
	*attr = NULL;
	return (-1);
}

static int	percent(t_attr *attr)
{
	char	*str;
	int		len;

	str = ft_strdup("%");
	len = ft_format_output_str(attr, str);
	free(str);
	return (len);
}

int			ft_print_conv(char **format, va_list arg)
{
	t_attr	*attr;
	int		len;

	attr = ft_get_attr(format, arg);
	len = 0;
	if (attr->conv == 0)
		return (abort_(&attr));
	else if (ft_strchr("diuoxXb", attr->conv))
		len = ft_ifdigit(attr, arg);
	else if (attr->conv == 's' || attr->conv == 'S')
		len = ft_ifstr(attr, arg);
	else if (attr->conv == 'c' || attr->conv == 'C')
		len = ft_ifchar(attr, arg);
	else if (attr->conv == 'f')
		len = ft_iffloat(attr, arg);
	else if (attr->conv == 'p')
		len = ft_ifptr(attr, arg);
	else if (attr->conv == '%')
		len = percent(attr);
	free(attr);
	return (len);
}
