/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:25:23 by gshona            #+#    #+#             */
/*   Updated: 2020/11/01 12:46:39 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static	void	inc(int *hi, int *lo)
{
	int	tmp;
	int	f;

	f = 0;
	tmp = *lo;
	while (tmp > 0 && !f)
	{
		if (tmp % 10 != 9)
			f = 1;
		tmp /= 10;
	}
	if (!f)
	{
		*lo = 0;
		*hi = (*hi < 0) ? *hi - 1 : *hi + 1;
	}
	else
	{
		*lo = *lo + 1;
	}
}

static	void	add_zeros(char **lo, int pres)
{
	int		len;
	int		zeros;
	char	*tmp;

	len = ft_strlen(*lo);
	zeros = pres - len;
	if (zeros <= 0)
		return ;
	tmp = ft_stralloc(zeros);
	ft_memset(tmp, (int)'0', zeros);
	ft_strappend(lo, tmp);
	free(tmp);
}

static int		ft_mod(int n)
{
	return ((n < 0) ? -n : n);
}

char			*ft_dtoa(double val, int pres)
{
	int			hi;
	int			lo;
	double		rem;
	char		*tmp;
	char		*res;

	hi = (int)val;
	val = (val < 0) ? -val : val;
	rem = (val - ft_mod(hi)) * ft_pow(10, (pres > 9) ? 9 : pres);
	lo = (int)rem;
	rem -= lo;
	if (rem >= 0.5)
		inc(&hi, &lo);
	res = ft_itoa_base(hi, 10, 0);
	if (pres == 0)
		return (res);
	ft_strappend(&res, ".");
	tmp = ft_itoa_base(lo, 10, 0);
	add_zeros(&tmp, pres);
	ft_strappend(&res, tmp);
	free(tmp);
	return (res);
}
