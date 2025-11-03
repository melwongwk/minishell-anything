/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:54:34 by melwong           #+#    #+#             */
/*   Updated: 2025/10/23 19:54:57 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/* 
char	*ft_strrchr(const char *s, int c)
{
	size_t	count;

	count = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *) &s[count]);
	if (count == 0)
		return (NULL);
	count -= 1;
	while (count > 0)
	{
		if (s[count] == (char)c)
			return ((char *) &s[count]);
		count--;
	}
	if (s[count] == (char)c)
		return ((char *) &s[count]);
	return (NULL);
}
*/

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	int		last;

	i = 0;
	last = -1;
	while (s[i])
	{
		if (s[i] == (char)c)
			last = i;
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	else if (last == -1)
		return (NULL);
	else
		return ((char *)(s + last));
}
