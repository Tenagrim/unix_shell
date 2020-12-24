/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_output_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:25:45 by gshona            #+#    #+#             */
/*   Updated: 2020/11/09 19:27:46 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void			print_spaces(int count, char space)
{
	int i;

	if (count <= 0)
		return ;
	i = 0;
	while (i++ < count)
		write(1, &space, 1);
}

static void			putchar_(char c)
{
	write(1, &c, 1);
}

int					ft_format_output_char(t_attr *attr, char str)
{
	int		spaces;
	int		len;
	char	space;

	len = (attr->precision != -1 && attr->precision > -1) ?
		ft_min(attr->precision, 1) : 1;
	space = (attr->flags & FLAG_ZERO && !(attr->flags & FLAG_MINUS)) ? '0' :
		' ';
	space = (attr->conv == '%' && attr->flags & FLAG_ZERO &&
			!(attr->flags & FLAG_MINUS)) ? '0' : space;
	spaces = (attr->width != -1) ? attr->width - len : 0;
	spaces = (spaces < 0) ? 0 : spaces;
	if (attr->flags & FLAG_MINUS)
	{
		putchar_(str);
		print_spaces(spaces, space);
	}
	else
	{
		print_spaces(spaces, space);
		putchar_(str);
	}
	return (len + spaces);
}
