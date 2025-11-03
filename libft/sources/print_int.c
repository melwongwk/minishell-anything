/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:04:34 by melwong           #+#    #+#             */
/*   Updated: 2025/07/13 15:56:32 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

/* static void	pad_chars(char c, int count)
{
	while (count-- > 0)
		write(1, &c, 1);
}

static void	set_padding_and_write_prefix(t_format *fmt, int *total_len,
				int *padding, char sign)
{
	if (sign)
		(*total_len)++;
	if (fmt->width > *total_len)
		*padding = fmt->width - *total_len;
	else
		*padding = 0;
	if (!fmt->dash && (!fmt->zero || fmt->precision >= 0))
		pad_chars(' ', *padding);
	if (sign)
		write(1, &sign, 1);
	if (!fmt->dash && fmt->zero && fmt->precision < 0)
		pad_chars('0', *padding);
}

static char	*set_str_and_sign(int nbr, t_format *fmt, char *sign)
{
	if (nbr == INT_MIN)
	{
		*sign = '-';
		return (ft_strdup("2147483648"));
	}
	if (nbr < 0)
	{
		*sign = '-';
		nbr = -nbr;
	}
	else if (fmt->plus)
		*sign = '+';
	else if (fmt->space)
		*sign = ' ';
	return (ft_itoa(nbr));
}

static char	*apply_precision(t_format *fmt, char *str, int *str_len)
{
	int		pad_len;
	char	*zero_str;
	char	*temp;

	if (fmt->precision == 0 && str[0] == '0')
	{
		free(str);
		*str_len = 0;
		return (ft_strdup(""));
	}
	if (fmt->precision > *str_len)
	{
		pad_len = fmt->precision - *str_len;
		zero_str = malloc(pad_len + 1);
		if (!zero_str)
			return (NULL);
		ft_memset(zero_str, '0', pad_len);
		zero_str[pad_len] = '\0';
		temp = ft_strjoin(zero_str, str);
		free(zero_str);
		free(str);
		str = temp;
		*str_len = ft_strlen(str);
	}
	return (str);
}

int	print_int_bonus(int nbr, t_format *fmt)
{
	char	*str;
	char	sign;
	int		str_len;
	int		total_len;
	int		padding;

	sign = 0;
	str = set_str_and_sign(nbr, fmt, &sign);
	if (!str)
		return (0);
	str_len = ft_strlen(str);
	str = apply_precision(fmt, str, &str_len);
	if (!str)
		return (0);
	total_len = str_len;
	set_padding_and_write_prefix(fmt, &total_len, &padding, sign);
	write(1, str, str_len);
	if (fmt->dash)
		pad_chars(' ', padding);
	free(str);
	if (fmt->width > total_len)
		return (fmt->width);
	return (total_len);
}
*/

static char	*get_int_string(int nbr, const char **prefix, t_format *fmt)
{
	if (nbr == INT_MIN)
	{
		*prefix = "-";
		return (ft_strdup("2147483648"));
	}
	if (nbr < 0)
	{
		*prefix = "-";
		nbr = -nbr;
	}
	else if (fmt->plus)
		*prefix = "+";
	else if (fmt->space)
		*prefix = " ";
	return (ft_itoa(nbr));
}

static void	set_int_flags(int nbr, t_format *fmt, int str_len)
{
	fmt->hash = 0;
	if (nbr < 0)
	{
		fmt->space = 0;
		fmt->plus = 0;
	}
	if (fmt->plus)
		fmt->space = 0;
	if (fmt->precision != -1 || fmt->dash)
		fmt->zero = 0;
	if (fmt->precision != -1 && fmt->precision < str_len)
		fmt->precision = str_len;
}

int	ft_print_int(int nbr, t_format *fmt)
{
	char		*str;
	const char	*prefix;
	int			print_len;

	prefix = NULL;
	if (fmt->precision == 0 && nbr == 0)
		return (width_padding(fmt->width, 0, 0));
	str = get_int_string(nbr, &prefix, fmt);
	if (!str)
		return (0);
	set_int_flags(nbr, fmt, ft_strlen(str));
	print_len = 0;
	format_and_print(str, fmt, prefix, &print_len);
	free(str);
	return (print_len);
}
