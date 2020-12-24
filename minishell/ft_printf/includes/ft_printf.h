/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshona <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:24:35 by gshona            #+#    #+#             */
/*   Updated: 2020/12/24 11:11:52 by gshona           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <libft.h>
# include <stdarg.h>

# define FLAGS		"+-0# "
# define SIZES		"lhL"
# define CONVERSIONS	"cCsSpdiouxXf%"
# define FLAG_PLUS	1
# define FLAG_MINUS	2
# define FLAG_ZERO	4
# define FLAG_SHARP	8
# define FLAG_SPACE	16
# define SIZE_L		32
# define SIZE_LL	64
# define SIZE_H		128
# define SIZE_HH	256
# define SIZE_UP_L	512
# define FLAG_DOT	1024

typedef struct		s_attr
{
	int				width;
	int				precision;
	int				flags;
	char			conv;
	int				wid;
	int				unset_wid;
}					t_attr;
int					ft_min(int a, int b);
int					ft_max(int a, int b);
int					ft_pow(int val, int pow);
int					ft_abs(int a);
char				*ft_dtoa(double val, int pres);
int					ft_printf(const char *format, ...);
t_attr				*ft_new_attr(void);
t_attr				*ft_get_attr(char **format, va_list arg);
int					ft_get_flags(char **format);
int					ft_get_width(char **format, va_list arg, t_attr *attr);
int					ft_get_precision(char **format, va_list arg);
int					ft_get_size(char **format);
char				ft_get_conv(char **format);
char				*ft_itoa_base(int value, int base, int upcase);
char				*ft_itoa_base_u(unsigned int value, int base, int up);
char				*ft_itoa_base_ul(unsigned long int value, int base, int up);
char				*ft_itoa_base_ull(unsigned long long int value,
		int base, int up);
char				*ft_itoa_base_uh(unsigned short int value,
		int base, int up);
char				*ft_itoa_base_uhh(unsigned char value, int base, int up);
char				*ft_itoa_base_l(long int value, int base, int upcase);
char				*ft_itoa_base_ll(long long int value, int base, int upcase);
char				*ft_itoa_base_h(short int value, int base, int upcase);
char				*ft_itoa_base_hh(char value, int base, int upcase);
int					ft_format_output_str(t_attr *attr, char *str);
int					ft_format_output_digit(t_attr *attr, char *str);
int					ft_format_output_ptr(t_attr *attr, char *str);
int					ft_ifdigit(t_attr *attr, va_list arg);
int					ft_ifptr(t_attr *attr, va_list arg);
int					ft_print_conv(char **format, va_list arg);
int					ft_ifstr(t_attr *attr, va_list arg);
int					ft_ifchar(t_attr *attr, va_list arg);
int					ft_iffloat(t_attr *attr, va_list arg);
int					ft_format_output_float(t_attr *attr, char *str);
int					ft_format_output_char(t_attr *attr, char str);
size_t				ft_str_len(char *str);
#endif
