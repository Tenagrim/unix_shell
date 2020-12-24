/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:26:06 by gshona            #+#    #+#             */
/*   Updated: 2020/11/01 12:26:17 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	ft_get_conv(char **format)
{
	char	res;

	res = 0;
	if (ft_strchr(CONVERSIONS, **format))
		res = **format;
	return (res);
}
