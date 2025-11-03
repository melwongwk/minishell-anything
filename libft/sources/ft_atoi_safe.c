/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:19:19 by melwong           #+#    #+#             */
/*   Updated: 2025/07/15 12:45:40 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static const char	*sign_check(const char *str, int *sign)
{
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

/*This function returns 1 or 0 depending on if the string that is parsed
through contains a valid number within the signed int range*/
int	ft_atoi_safe(const char *str, int *out)
{
	int		sign;
	long	number;

	if (!str || !*str)
		return (0);
	sign = 1;
	while (ft_isspace(*str))
		str++;
	str = sign_check(str, &sign);
	if (!ft_isdigit(*str))
		return (0);
	number = 0;
	while (ft_isdigit(*str))
	{
		number = (*str - '0') + (number * 10);
		if ((sign == 1 && number > INT_MAX)
			|| (sign == -1 && -(number) < INT_MIN))
			return (0);
		str++;
	}
	if (*str != '\0' && !ft_isspace(*str))
		return (0);
	*out = (int)(sign * number);
	return (1);
}
