/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:56:34 by melwong           #+#    #+#             */
/*   Updated: 2025/07/15 12:16:46 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_swap(void *a, void *b, size_t size)
{
	unsigned char	*pa;
	unsigned char	*pb;
	unsigned char	temp;

	if (a == b || size == 0)
		return ;
	pa = (unsigned char *)a;
	pb = (unsigned char *)b;
	while (size--)
	{
		temp = *pa;
		*pa++ = *pb;
		*pb++ = temp;
	}
}
