/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:28:03 by melwong           #+#    #+#             */
/*   Updated: 2025/10/23 19:40:45 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;

	if ((!dest || !src) && n > 0)
		return (NULL);
	dest_ptr = (unsigned char *)dest;
	src_ptr = (const unsigned char *)src;
	if (n == 0 || dest_ptr == src_ptr)
		return (dest);
	if (dest_ptr < src_ptr)
		ft_memcpy(dest, src, n);
	else
	{
		dest_ptr += n;
		src_ptr += n;
		while (n)
		{
			--dest_ptr;
			--src_ptr;
			*dest_ptr = *src_ptr;
			n--;
		}
	}
	return (dest);
}
