/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:55:18 by melwong           #+#    #+#             */
/*   Updated: 2025/07/13 15:55:11 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

/*
static void	print_with_padding(char *str, t_format *fmt,
				int *total_len, int str_len)
{
	if (!fmt->dash)
	{
		while (fmt->width > *total_len)
		{
			write(1, " ", 1);
			(*total_len)++;
		}
	}
	write(1, str, str_len);
	if (fmt->dash)
	{
		while (fmt->width > *total_len)
		{
			write(1, " ", 1);
			(*total_len)++;
		}
	}
}

static char	*ft_utoa_ptr(unsigned long nbr)
{
	char	buffer[17];
	char	*base;
	int		i;
	char	*hex;
	char	*str;

	base = BASE_LOWER;
	i = 0;
	buffer[16] = '\0';
	while (nbr)
	{
		buffer[15 - i] = base[nbr % 16];
		nbr /= 16;
		i++;
	}
	hex = ft_strdup(&buffer[16 - i]);
	str = ft_strjoin("0x", hex);
	free(hex);
	return (str);
}

int	print_ptr_bonus(void *ptr, t_format *fmt)
{
	int				str_len;
	int				total_len;
	unsigned long	n;
	char			*str;

	n = (unsigned long)ptr;
	if (n == 0)
		str = ft_strdup("(nil)");
	else
		str = ft_utoa_ptr(n);
	if (!str)
		return (0);
	str_len = ft_strlen(str);
	total_len = str_len;
	print_with_padding(str, fmt, &total_len, str_len);
	free(str);
	return (total_len);
}
 */

static char	*get_ptr_string(unsigned long nbr, const char *prefix)
{
	char	*nstr;
	char	*str;

	nstr = ft_ultoa_base(nbr, BASE_LOWER);
	str = ft_strjoin(prefix, nstr);
	free(nstr);
	return (str);
}

static void	set_ptr_flags(unsigned long nbr, t_format *fmt, int str_len)
{
	fmt->space = 0;
	fmt->plus = 0;
	fmt->hash = 0;
	if (fmt->precision != -1 || fmt->dash || nbr == 0)
		fmt->zero = 0;
	if (fmt->precision != -1 && fmt->precision < str_len)
		fmt->precision = str_len;
}

int	ft_print_p(void *ptr, t_format *fmt)
{
	char			*str;
	const char		*prefix;
	int				print_len;
	unsigned long	nbr;

	prefix = NULL;
	nbr = (unsigned long)ptr;
	if (nbr == 0)
		str = ft_strdup("(nil)");
	else
	{
		prefix = "0x";
		str = get_ptr_string(nbr, prefix);
		prefix = NULL;
	}
	if (!str)
		return (0);
	set_ptr_flags(nbr, fmt, ft_strlen(str));
	print_len = 0;
	format_and_print(str, fmt, prefix, &print_len);
	free(str);
	return (print_len);
}
