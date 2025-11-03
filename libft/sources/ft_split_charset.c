/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:24:13 by melwong           #+#    #+#             */
/*   Updated: 2025/07/15 21:38:33 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_separator(char c, const char *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

static char	*malloc_word(const char *str, const char *charset)
{
	char	*word;
	int		len;

	len = 0;
	while (str[len] && !is_separator(str[len], charset))
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, str, len + 1);
	return (word);
}

static char	**free_all(char **result, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

char	**ft_split_charset(const char *str, const char *charset)
{
	char	**res;
	int		i;

	if (!str || !charset)
		return (NULL);
	res = malloc(sizeof(char *) * (ft_count_words_charset(str, charset) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (!is_separator(*str, charset))
		{
			res[i] = malloc_word(str, charset);
			if (!res[i])
				return (free_all(res, i));
			i++;
			while (*str && !is_separator(*str, charset))
				str++;
		}
		else
			str++;
	}
	res[i] = NULL;
	return (res);
}
