/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:24:00 by melwong           #+#    #+#             */
/*   Updated: 2025/07/13 15:56:03 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

/* 
static void	pad_spaces_or_zeros(t_format *fmt, int *total_len)
{
	while (fmt->width > *total_len)
	{
		if (fmt->zero && fmt->precision == -1)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		(*total_len)++;
	}
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

static char	*ft_utoa(unsigned int nbr)
{
	char			*str;
	int				len;
	unsigned int	n;

	if (nbr == 0)
		return (ft_strdup("0"));
	n = nbr;
	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}

int	print_unsigned_bonus(unsigned int nbr, t_format *fmt)
{
	char	*str;
	int		str_len;
	int		total_len;

	if (nbr == 0 && fmt->precision == 0)
		str = ft_strdup("");
	else
		str = ft_utoa(nbr);
	if (!str)
		return (0);
	str = apply_precision(&str_len, fmt->precision, str);
	if (!str)
		return (0);
	total_len = str_len;
	if (!fmt->dash)
		pad_spaces_or_zeros(fmt, &total_len);
	write(1, str, str_len);
	if (fmt->dash)
		pad_spaces_or_zeros(fmt, &total_len);
	free(str);
	return (total_len);
}
*/

static void	set_uint_flags(t_format *fmt, int str_len)
{
	fmt->hash = 0;
	fmt->space = 0;
	fmt->plus = 0;
	if (fmt->precision != -1 || fmt->dash)
		fmt->zero = 0;
	if (fmt->precision != -1 && fmt->precision < str_len)
		fmt->precision = str_len;
}

int	ft_print_u(unsigned int nbr, t_format *fmt)
{
	char		*str;
	const char	*prefix;
	int			print_len;

	prefix = NULL;
	if (fmt->precision == 0 && nbr == 0)
		return (width_padding(fmt->width, 0, 0));
	str = ft_ultoa_base(nbr, "0123456789");
	if (!str)
		return (0);
	set_uint_flags(fmt, ft_strlen(str));
	print_len = 0;
	format_and_print(str, fmt, prefix, &print_len);
	free(str);
	return (print_len);
}
