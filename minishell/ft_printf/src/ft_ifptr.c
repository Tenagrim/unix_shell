/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:29:12 by gshona            #+#    #+#             */
/*   Updated: 2020/11/09 19:28:36 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		ft_ifptr(t_attr *attr, va_list arg)
{
	char			*str;
	int				len;
	void			*tmp;

	tmp = va_arg(arg, void*);
	if (!tmp)
	{
		str = ft_strdup("0x0");
		attr->precision = (attr->precision == 0) ? 2 : attr->precision;
		attr->precision = (attr->precision == -1) ? 3 : attr->precision;
		len = ft_format_output_str(attr, str);
		free(str);
		return (len);
	}
	str = ft_itoa_base_ul((unsigned long int)tmp, 16, 0);
	len = ft_format_output_ptr(attr, str);
	free(str);
	return (len);
}
