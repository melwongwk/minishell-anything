/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:43:09 by melwong           #+#    #+#             */
/*   Updated: 2025/06/11 22:47:31 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

const char	*parse_flags(const char *format, t_format *fmt)
{
	while (*format == ' ' || *format == '-' || *format == '0'
		|| *format == '+' || *format == '#')
	{
		if (*format == ' ')
			fmt->space = 1;
		if (*format == '-')
			dash_flag(fmt);
		if (*format == '0' && fmt->dash == 0)
			fmt->zero = 1;
		if (*format == '+')
			fmt->plus = 1;
		if (*format == '#')
			fmt->hash = 1;
		format++;
	}
	return (format);
}

const char	*parse_width(const char *format, t_format *fmt)
{
	while (ft_isdigit(*format))
	{
		fmt->width = (*format - '0') + (fmt->width * 10);
		format++;
	}
	return (format);
}

const char	*parse_precision(const char *format, t_format *fmt)
{
	if (*format == '.')
	{
		format++;
		fmt->precision = 0;
		while (ft_isdigit(*format))
		{
			fmt->precision = (*format - '0') + (fmt->precision * 10);
			format++;
		}
	}
	return (format);
}

const char	*parse_specifier(const char *format, t_format *fmt)
{
	if (*format == 'c' || *format == 's' || *format == 'p'
		|| *format == 'd' || *format == 'i' || *format == 'u'
		|| *format == 'x' || *format == 'X' || *format == '%')
	{
		fmt->spec = *format;
		format++;
	}
	return (format);
}

int	handle_conversion(t_format *fmt, va_list args)
{
	if (fmt->spec == 'c')
		return (ft_print_c(va_arg(args, int), fmt));
	else if (fmt->spec == 's')
		return (ft_print_s(va_arg(args, char *), fmt));
	else if (fmt->spec == 'p')
		return (ft_print_p(va_arg(args, void *), fmt));
	else if (fmt->spec == 'd' || fmt->spec == 'i')
		return (ft_print_int(va_arg(args, int), fmt));
	else if (fmt->spec == 'u')
		return (ft_print_u(va_arg(args, unsigned int), fmt));
	else if (fmt->spec == 'x' || fmt->spec == 'X')
		return (ft_print_x(va_arg(args, unsigned int), fmt->spec, fmt));
	else if (fmt->spec == '%')
		return (ft_print_percent());
	return (0);
}
