/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_hh.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:30:31 by gshona            #+#    #+#             */
/*   Updated: 2020/11/01 12:36:17 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int		get_char(int nb, int upcase)
{
	if (nb >= 10)
		if (upcase)
			return (nb - 10 + 'A');
		else
			return (nb - 10 + 'a');
	else
		return (nb + '0');
}

static int		calc_digs(char value, int base)
{
	int len;

	len = 1;
	if (value < 0)
	{
		len++;
		value = -value;
	}
	while (value >= base)
	{
		value /= base;
		len++;
	}
	return (len);
}

char			*ft_itoa_base_hh(char value, int base, int upcase)
{
	int				i;
	char			*res;
	int				tmp;
	int				sign;

	if (value == -128)
		return (ft_strdup("-128"));
	i = calc_digs(value, base);
	if (!(res = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (value < 0)
		res[0] = '-';
	sign = value < 0;
	tmp = (value < 0) ? -value : value;
	value = (value < 0) ? -value : value;
	res[i--] = '\0';
	while (i >= sign)
	{
		tmp = value % base;
		res[i] = get_char(tmp, upcase);
		value /= base;
		i--;
	}
	return (res);
}
