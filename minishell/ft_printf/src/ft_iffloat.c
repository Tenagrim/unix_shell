/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iffloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:28:57 by gshona            #+#    #+#             */
/*   Updated: 2020/11/01 12:29:11 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_iffloat(t_attr *attr, va_list arg)
{
	char	*str;
	double	num;
	int		len;
	int		pres;

	pres = (attr->precision == -1) ? 6 : attr->precision;
	num = va_arg(arg, double);
	str = ft_dtoa(num, pres);
	len = ft_format_output_float(attr, str);
	free(str);
	return (len);
}
