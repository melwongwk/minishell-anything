/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 05:28:19 by melwong           #+#    #+#             */
/*   Updated: 2025/10/24 05:28:56 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ultoa_base(unsigned long nbr, const char *base)
{
	char	buffer[64];
	int		i;
	int		base_len;

	base_len = ft_strlen(base);
	buffer[63] = '\0';
	if (nbr == 0)
	{
		buffer[62] = base[0];
		return (ft_strdup(&buffer[62]));
	}
	i = 0;
	while (nbr)
	{
		buffer[62 - i] = base[nbr % base_len];
		i++;
		nbr /= base_len;
	}
	return (ft_strdup(&buffer[63 - i]));
}
