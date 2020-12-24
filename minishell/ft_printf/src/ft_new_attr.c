/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_attr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:33:01 by gshona            #+#    #+#             */
/*   Updated: 2020/11/01 12:33:08 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

t_attr	*ft_new_attr(void)
{
	t_attr	*res;

	res = (t_attr*)malloc(sizeof(t_attr));
	res->width = -1;
	res->flags = 0;
	res->precision = -1;
	res->conv = 0;
	return (res);
}
