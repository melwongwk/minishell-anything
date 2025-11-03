/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:26:30 by melwong           #+#    #+#             */
/*   Updated: 2025/07/13 15:54:28 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

/* static char	*prefix_padding(char spec, t_format *fmt,
				int *total_len, unsigned int nbr)
{
	char	*prefix;

	if (fmt->hash && nbr != 0)
	{
		if (spec == 'x')
			prefix = "0x";
		else
			prefix = "0X";
	}
	else
		prefix = NULL;
	if (prefix)
		(*total_len) += 2;
	if (fmt->zero && fmt->precision == -1)
		write(1, prefix, 2);
	while (!fmt->dash && fmt->width > *total_len)
	{
		if (fmt->zero && fmt->precision == -1)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		(*total_len)++;
	}
	return (prefix);
}

static char	*apply_precision(int *str_len, int precision, char *str)
{
	char	*zero_str;
	char	*temp;
	int		pad_len;

	*str_len = ft_strlen(str);
	if (precision > *str_len)
	{
		pad_len = precision - *str_len;
		zero_str = malloc(sizeof(char) * (pad_len + 1));
		if (!zero_str)
		{
			free(str);
			return (NULL);
		}
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

static char	*ft_utoa_hex(unsigned int nbr, const char spec)
{
	char	buffer[9];
	int		i;
	char	*base;

	if (spec == 'X')
		base = BASE_UPPER;
	else
		base = BASE_LOWER;
	if (nbr == 0)
		return (ft_strdup("0"));
	i = 0;
	buffer[8] = '\0';
	while (nbr)
	{
		buffer[7 - i] = base[nbr % 16];
		i++;
		nbr /= 16;
	}
	return (ft_strdup(&buffer[8 - i]));
}

static char	*set_hex_str(t_format *fmt, const char spec,
				unsigned int n)
{
	if (n == 0 && fmt->precision == 0)
		return (ft_strdup(""));
	else
		return (ft_utoa_hex(n, spec));
}

int	print_hex_bonus(unsigned int nbr, const char spec, t_format *fmt)
{
	char	*str;
	char	*prefix;
	int		str_len;
	int		total_len;

	str = set_hex_str(fmt, spec, nbr);
	if (!str)
		return (0);
	str = apply_precision(&str_len, fmt->precision, str);
	if (!str)
		return (0);
	total_len = str_len;
	prefix = prefix_padding(spec, fmt, &total_len, nbr);
	if (prefix && !(fmt->zero && fmt->precision == -1))
		write(1, prefix, 2);
	write(1, str, str_len);
	while (fmt->dash && fmt->width > total_len)
	{
		write(1, " ", 1);
		total_len++;
	}
	free(str);
	return (total_len);
} */

static char	*get_hex_string(unsigned int nbr, const char spec)
{
	char	*base;

	if (spec == 'X')
		base = BASE_UPPER;
	else
		base = BASE_LOWER;
	return (ft_ultoa_base(nbr, base));
}

static void	set_hex_flags(unsigned int nbr, t_format *fmt, int str_len)
{
	fmt->space = 0;
	fmt->plus = 0;
	if (nbr == 0)
		fmt->hash = 0;
	if (fmt->hash)
		fmt->width -= 2;
	if (fmt->precision != -1 || fmt->dash)
		fmt->zero = 0;
	if (fmt->precision != -1 && fmt->precision < str_len)
		fmt->precision = str_len;
}

int	ft_print_x(unsigned int nbr, const char spec, t_format *fmt)
{
	char		*str;
	const char	*prefix;
	int			print_len;

	prefix = NULL;
	if (fmt->precision == 0 && nbr == 0)
		return (width_padding(fmt->width, 0, 0));
	str = get_hex_string(nbr, spec);
	if (!str)
		return (0);
	set_hex_flags(nbr, fmt, ft_strlen(str));
	if (fmt->hash && spec == 'X')
		prefix = "0X";
	else if (fmt->hash && spec == 'x')
		prefix = "0x";
	print_len = 0;
	format_and_print(str, fmt, prefix, &print_len);
	free(str);
	return (print_len);
}
