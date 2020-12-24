/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:31:11 by gshona            #+#    #+#             */
/*   Updated: 2020/11/01 12:34:27 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <limits.h>

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

static int		calc_digs(long long int value, int base)
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

char			*ft_itoa_base_ll(long long int value, int base, int upcase)
{
	int				i;
	char			*res;
	int				tmp;
	int				sign;

	if (value == LONG_MIN)
		return (ft_strdup("-9223372036854775808"));
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
