/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:27:58 by gshona            #+#    #+#             */
/*   Updated: 2020/11/11 17:29:53 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int			get_base(t_attr *attr)
{
	if (attr->conv == 'i' || attr->conv == 'd' || attr->conv == 'u')
		return (10);
	else if (attr->conv == 'b')
		return (2);
	else if (attr->conv == 'x' || attr->conv == 'X')
		return (16);
	else if (attr->conv == 'o')
		return (8);
	return (10);
}

static char			*if_signed(t_attr *attr, va_list arg)
{
	char	*str;
	int		upc;

	upc = attr->conv == 'X';
	if (attr->flags & SIZE_L)
		str = ft_itoa_base_l(va_arg(arg, long int), get_base(attr), upc);
	else if (attr->flags & SIZE_LL)
		str = ft_itoa_base_ll(va_arg(arg, long long int), get_base(attr), upc);
	else if (attr->flags & SIZE_H)
		str = ft_itoa_base_h((short int)va_arg(arg, int), get_base(attr), upc);
	else if (attr->flags & SIZE_HH)
		str = ft_itoa_base_hh((char)va_arg(arg, int), get_base(attr), upc);
	else
		str = ft_itoa_base(va_arg(arg, int), get_base(attr), upc);
	return (str);
}

static char			*if_unsigned(t_attr *attr, va_list arg)
{
	char	*str;
	int		upc;

	upc = attr->conv == 'X';
	if (attr->flags & SIZE_L)
		str = ft_itoa_base_ul(va_arg(arg, unsigned long int),
				get_base(attr), upc);
	else if (attr->flags & SIZE_LL)
		str = ft_itoa_base_ull(va_arg(arg, unsigned long long int),
				get_base(attr), upc);
	else if (attr->flags & SIZE_H)
		str = ft_itoa_base_uh((unsigned short int)va_arg(arg, unsigned int),
				get_base(attr), upc);
	else if (attr->flags & SIZE_HH)
		str = ft_itoa_base_uhh((unsigned char)va_arg(arg, unsigned int),
				get_base(attr), upc);
	else
		str = ft_itoa_base_u(va_arg(arg, unsigned int), get_base(attr), upc);
	return (str);
}

int					ft_ifdigit(t_attr *attr, va_list arg)
{
	char	*str;
	int		len;

	if (attr->conv == 'u' || attr->conv == 'x' || attr->conv == 'X')
		str = if_unsigned(attr, arg);
	else
		str = if_signed(attr, arg);
	if (str[0] != '0' && attr->precision == 0)
	{
		attr->precision = -1;
		attr->wid = 1;
	}
	len = ft_format_output_digit(attr, str);
	free(str);
	return (len);
}
