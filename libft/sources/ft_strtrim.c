/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 21:30:21 by melwong           #+#    #+#             */
/*   Updated: 2025/10/23 21:31:48 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static int	is_set(const char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, char const *set)
{
	char	*trimmed;
	size_t	head;
	size_t	tail;

	if (!s1 || !set)
		return (NULL);
	head = 0;
	while (s1[head] && is_set(s1[head], set))
		head++;
	tail = ft_strlen(s1);
	while (tail > head && is_set(s1[tail - 1], set))
		tail--;
	trimmed = ft_substr(s1, head, tail - head);
	return (trimmed);
}
