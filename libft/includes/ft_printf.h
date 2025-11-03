/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:59:42 by melwong           #+#    #+#             */
/*   Updated: 2025/10/27 20:59:46 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

# define BASE_UPPER "0123456789ABCDEF"
# define BASE_LOWER "0123456789abcdef"

typedef struct s_format
{
	int		zero;
	int		dash;
	int		space;
	int		plus;
	int		hash;
	int		width;
	int		precision;
	char	spec;
}			t_format;

int			ft_print_c(int c, t_format *fmt);
int			ft_print_s(const char *s, t_format *fmt);
int			ft_print_p(void *ptr, t_format *fmt);
int			ft_print_int(int nbr, t_format *fmt);
int			ft_print_u(unsigned int nbr, t_format *fmt);
int			ft_print_x(unsigned int nbr, char spec, t_format *fmt);
int			ft_print_percent(void);
int			handle_conversion(t_format *fmt, va_list args);
int			width_padding(int width, int len, int zero);
void		dash_flag(t_format *fmt);
void		format_and_print(char *str, t_format *fmt,
				const char *prefix, int *print_len);
const char	*parse_flags(const char *format, t_format *fmt);
const char	*parse_width(const char *format, t_format *fmt);
const char	*parse_precision(const char *format, t_format *fmt);
const char	*parse_specifier(const char *format, t_format *fmt);

#endif
