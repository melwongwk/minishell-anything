/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:44:21 by melwong           #+#    #+#             */
/*   Updated: 2025/06/22 16:29:59 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

static int	print_string_precision(const char *s, int precision, int len)
{
	int	i;

	i = 0;
	if (precision != -1)
	{
		while (s[i] && i < len)
		{
			ft_putchar_fd(s[i], 1);
			i++;
		}
		return (i);
	}
	else
	{
		ft_putstr_fd((char *)s, 1);
		return (ft_strlen(s));
	}
}

static int	check_precision(int len, int precision)
{
	if (precision >= 0 && precision < len)
		return (precision);
	return (len);
}

int	ft_print_s(const char *s, t_format *fmt)
{
	int	print_len;
	int	str_len;

	if (s == NULL)
	{
		if (fmt->precision > -1 && fmt->precision < 6)
			s = "";
		else
			s = "(null)";
	}
	str_len = check_precision(ft_strlen(s), fmt->precision);
	print_len = 0;
	if (fmt->dash)
		print_len += print_string_precision(s, fmt->precision, str_len);
	print_len += width_padding(fmt->width, str_len, 0);
	if (!fmt->dash)
		print_len += print_string_precision(s, fmt->precision, str_len);
	return (print_len);
}
