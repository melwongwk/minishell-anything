/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_charset.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:28:17 by melwong           #+#    #+#             */
/*   Updated: 2025/07/30 21:32:39 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_sep(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	ft_count_words_charset(const char *s, const char *charset)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (in_word == 0 && !is_sep(*s, charset))
		{
			count++;
			in_word = 1;
		}
		else if (is_sep(*s, charset))
			in_word = 0;
		s++;
	}
	return (count);
}
