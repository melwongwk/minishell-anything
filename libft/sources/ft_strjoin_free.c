/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 22:27:57 by melwong           #+#    #+#             */
/*   Updated: 2025/07/14 22:28:07 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_strjoin_null_cases(char *s1, char *s2, int to_free)
{
	char	*dup;

	if (!s1)
	{
		if (!s2)
			return (NULL);
		dup = ft_strdup(s2);
		if (to_free != 0)
			free(s2);
		return (dup);
	}
	if (!s2)
	{
		dup = ft_strdup(s1);
		if (to_free != 1)
			free(s1);
		return (dup);
	}
	return (NULL);
}

static void	ft_strjoin_cleanup(char *s1, char *s2, int to_free)
{
	if (to_free != 1)
		free(s1);
	if (to_free != 0)
		free(s2);
}

// to_free:
// 0 = free s1
// 1 = free s2
// 2 or more = free both
char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*joined;
	size_t	len1;
	size_t	len2;
	char	*early;

	early = ft_strjoin_null_cases(s1, s2, to_free);
	if (early)
		return (early);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
	{
		ft_strjoin_cleanup(s1, s2, to_free);
		return (NULL);
	}
	ft_memcpy(joined, s1, len1);
	ft_memcpy(joined + len1, s2, len2 + 1);
	ft_strjoin_cleanup(s1, s2, to_free);
	return (joined);
}
