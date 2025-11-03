/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:12:46 by melwong           #+#    #+#             */
/*   Updated: 2025/07/13 15:59:53 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_print_c(int c, t_format *fmt)
{
	if (fmt->dash)
		ft_putchar_fd(c, 1);
	width_padding(fmt->width, 1, 0);
	if (!fmt->dash)
		ft_putchar_fd(c, 1);
	if (fmt->width > 1)
		return (fmt->width);
	return (1);
}
