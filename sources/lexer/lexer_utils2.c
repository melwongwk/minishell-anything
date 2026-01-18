/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:38:09 by melwong           #+#    #+#             */
/*   Updated: 2026/01/18 10:39:04 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(const char *input, int *i, bool *had_space)
{
	while (ft_isspace(input[*i]))
	{
		*had_space = true;
		(*i)++;
	}
}

static char	*extract_segment(char *s, int *i, int *status, bool *is_var)
{
	*is_var = false;
	if (s[*i] == '$')
		return (handle_variable(s, i, status, is_var));
	if (s[*i] == '\'' || s[*i] == '"')
		return (handle_quotes(s, i, status));
	return (handle_word(s, i, status));
}

t_token	*parse_token(char *input, int *i)
{
	int		status;
	bool	is_var;
	char	*seg;
	t_token	*new;

	seg = extract_segment(input, i, &status, &is_var);
	if (!seg)
		return (NULL);
	if (*seg)
	{
		if (is_var)
			new = token_new(seg, VAR, status);
		else
			new = token_new(seg, WORD, status);
		free(seg);
		return (new);
	}
	free(seg);
	return (NULL);
}
