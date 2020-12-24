/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_output_float.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:25:42 by gshona            #+#    #+#             */
/*   Updated: 2020/11/01 12:55:57 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		print_spaces(int count, char c)
{
	int i;

	if (count <= 0)
		return ;
	i = 0;
	while (i++ < count)
		write(1, &c, 1);
}

static int		print_num(t_attr *attr, char *str)
{
	int	len;

	len = 0;
	if (attr->flags & FLAG_PLUS)
	{
		ft_putchar('+');
		len++;
	}
	ft_putstr(str);
	return (len);
}

int				ft_format_output_float(t_attr *attr, char *str)
{
	int	spaces;
	int	len;

	len = (int)ft_strlen(str);
	spaces = (attr->width != -1) ? attr->width - len : 0;
	spaces = (attr->flags & FLAG_PLUS) ? spaces - 1 : spaces;
	if (attr->flags & FLAG_MINUS)
	{
		len = print_num(attr, str);
		print_spaces(spaces, ' ');
	}
	else
	{
		print_spaces(spaces, ' ');
		len = print_num(attr, str);
	}
	return (len + spaces);
}
