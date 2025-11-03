/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:43:29 by melwong           #+#    #+#             */
/*   Updated: 2025/07/15 21:14:16 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	*ft_split_int(const char *str, int *count)
{
	int		*array;
	int		i;
	int		temp;

	if (!str || !count)
		return (NULL);
	*count = ft_count_words(str, ' ');
	array = malloc(sizeof(int) * (*count));
	if (!array)
		return (NULL);
	i = 0;
	while (*str && i < *count)
	{
		if (!ft_atoi_safe(str, &temp))
		{
			free(array);
			return (NULL);
		}
		array[i++] = temp;
		while (*str && !ft_isspace(*str))
			str++;
		while (*str && ft_isspace(*str))
			str++;
	}
	return (array);
}
