/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:33:45 by gshona            #+#    #+#             */
/*   Updated: 2020/11/01 12:41:25 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_printf(const char *format, ...)
{
	int			count;
	va_list		arg;

	count = 0;
	va_start(arg, format);
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar(*format);
			count++;
		}
		else
		{
			format++;
			count += ft_print_conv((char**)(&format), arg);
		}
		format++;
	}
	va_end(arg);
	return (count);
}
