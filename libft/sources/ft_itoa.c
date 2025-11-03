/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 21:34:55 by melwong           #+#    #+#             */
/*   Updated: 2025/10/23 21:37:13 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

char	*ft_itoa(int n)
{
	char	str[12];
	int		i;
	int		neg;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	str[11] = '\0';
	neg = 0;
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	i = 0;
	while (n)
	{
		str[10 - i++] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		str[10 - i++] = '-';
	return (ft_strdup(&str[11 - i]));
}
