/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:56:56 by melwong           #+#    #+#             */
/*   Updated: 2026/01/18 10:56:58 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_variable(char *s, int *i, int *status, bool *is_var)
{
	int	start;

	start = *i;
	*is_var = true;
	(*i)++;
	if (s[*i] == '?')
		(*i)++;
	else
		while (ft_isalnum(s[*i]) || s[*i] == '_')
			(*i)++;
	*status = DEFAULT;
	return (ft_strndup(s + start, *i - start));
}

char	*handle_quotes(char *s, int *i, int *status)
{
	char	q;
	int		start;
	char	*out;

	q = s[*i];
	start = ++(*i);
	if (q == '\'')
		*status = SQUOTE;
	else
		*status = DQUOTE;
	while (s[*i] && s[*i] != q)
		(*i)++;
	out = ft_strndup(s + start, *i - start);
	if (s[*i] == q)
		(*i)++;
	else
	{
		free(out);
		return (NULL);
	}
	return (out);
}

char	*handle_word(char *s, int *i, int *status)
{
	int	start;

	start = *i;
	while (s[*i] && !ft_isspace(s[*i])
		&& !is_redir(s[*i]) && s[*i] != '|'
		&& s[*i] != '$' && s[*i] != '\'' && s[*i] != '"')
		(*i)++;
	*status = DEFAULT;
	return (ft_strndup(s + start, *i - start));
}
