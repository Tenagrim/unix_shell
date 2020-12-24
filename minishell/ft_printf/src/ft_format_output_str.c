/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_output_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:25:45 by gshona            #+#    #+#             */
/*   Updated: 2020/11/09 19:34:33 by gshona           ###   ########.fr       */
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

static void			putstr_n(char *str, int n)
{
	int	i;

	i = 0;
	while (i < n && str[i])
	{
		write(1, str + i, 1);
		i++;
	}
}

int					ft_format_output_str(t_attr *attr, char *str)
{
	int		spaces;
	int		len;
	char	space;

	len = (attr->precision != -1 && attr->precision > -1) ?
		ft_min(attr->precision, ft_strlen(str)) : (int)ft_strlen(str);
	len = (attr->precision < 0 && !ft_strcmp(str, "(null)")) ? 6 : len;
	space = (attr->flags & FLAG_ZERO && !(attr->flags & FLAG_MINUS)) ? '0' :
		' ';
	space = (attr->conv == '%' && attr->flags & FLAG_ZERO &&
			!(attr->flags & FLAG_MINUS)) ? '0' : space;
	spaces = (attr->width != -1) ? attr->width - len : 0;
	spaces = (spaces < 0) ? 0 : spaces;
	if (attr->flags & FLAG_MINUS)
	{
		putstr_n(str, len);
		print_spaces(spaces, space);
	}
	else
	{
		print_spaces(spaces, space);
		putstr_n(str, len);
	}
	return (len + spaces);
}
