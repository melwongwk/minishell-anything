/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:55:45 by melwong           #+#    #+#             */
/*   Updated: 2025/07/15 13:54:10 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

static void	init_format(t_format *fmt)
{
	*fmt = (t_format){0};
	fmt->precision = -1;
}

static const char	*parse_format(const char *format, t_format *fmt)
{
	format = parse_flags(format, fmt);
	format = parse_width(format, fmt);
	format = parse_precision(format, fmt);
	format = parse_specifier(format, fmt);
	return (format);
}

static int	handle_format(const char *format, va_list args, t_format *fmt)
{
	int	count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format != '\0')
			{
				init_format(fmt);
				format = parse_format(format, fmt);
				count += handle_conversion(fmt, args);
			}
			else
				write(1, "%", 1);
		}
		else
		{
			write(1, format, 1);
			count++;
			format++;
		}
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_format	fmt;
	int			count;

	if (!format || *format == '\0')
		return (-1);
	va_start(args, format);
	count = 0;
	count += handle_format(format, args, &fmt);
	va_end(args);
	return (count);
}
