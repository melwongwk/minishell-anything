/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:57:56 by melwong           #+#    #+#             */
/*   Updated: 2025/07/13 15:58:11 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

void	dash_flag(t_format *fmt)
{
	fmt->dash = 1;
	fmt->zero = 0;
}

int	width_padding(int width, int len, int zero)
{
	int	count;

	count = 0;
	while (width > len)
	{
		if (zero)
		{
			write(1, "0", 1);
			count++;
		}
		else if (!zero)
		{
			write(1, " ", 1);
			count++;
		}
		width--;
	}
	return (count);
}

static int	print_prefix_and_zeros(const char *prefix, int zeros)
{
	int	print_len;

	print_len = 0;
	if (prefix)
	{
		write(1, prefix, ft_strlen(prefix));
		print_len += ft_strlen(prefix);
	}
	while (zeros-- > 0)
	{
		write(1, "0", 1);
		print_len++;
	}
	return (print_len);
}

void	format_and_print(char *str, t_format *fmt,
		const char *prefix, int *print_len)
{
	int	str_len;
	int	prefix_len;
	int	total_len;
	int	zeros;

	str_len = ft_strlen(str);
	prefix_len = 0;
	zeros = 0;
	if (prefix)
		prefix_len = ft_strlen(prefix);
	if (fmt->precision > str_len)
		zeros = fmt->precision - str_len;
	total_len = str_len + prefix_len + zeros;
	if (!fmt->dash && !fmt->zero)
		*print_len += width_padding(fmt->width, total_len, fmt->zero);
	*print_len += print_prefix_and_zeros(prefix, zeros);
	if (!fmt->dash && fmt->zero)
		*print_len += width_padding(fmt->width, total_len, fmt->zero);
	write(1, str, str_len);
	*print_len += str_len;
	if (fmt->dash)
		*print_len += width_padding(fmt->width, total_len, 0);
}
