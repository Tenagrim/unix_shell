/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ul.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:32:22 by gshona            #+#    #+#             */
/*   Updated: 2020/11/01 12:35:44 by gshona           ###   ########.fr       */
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

static int		calc_digs(unsigned long int value, int base)
{
	int len;

	len = 1;
	while (value >= (unsigned long int)base)
	{
		value /= base;
		len++;
	}
	return (len);
}

char			*ft_itoa_base_ul(unsigned long int value, int base, int up)
{
	int					i;
	char				*res;
	unsigned int		tmp;

	i = calc_digs(value, base);
	if (!(res = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	tmp = value;
	res[i--] = '\0';
	while (i >= 0)
	{
		tmp = value % base;
		res[i] = get_char(tmp, up);
		value /= base;
		i--;
	}
	return (res);
}
