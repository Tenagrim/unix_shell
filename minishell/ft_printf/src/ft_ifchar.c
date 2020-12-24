/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ifchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:27:45 by gshona            #+#    #+#             */
/*   Updated: 2020/11/09 18:27:44 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int				ft_ifchar(t_attr *attr, va_list arg)
{
	int		len;
	char	tmp;

	tmp = (char)va_arg(arg, int);
	len = ft_format_output_char(attr, tmp);
	return (len);
}
