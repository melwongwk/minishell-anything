/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:38:09 by melwong           #+#    #+#             */
/*   Updated: 2026/01/20 15:48:31 by hho-jia-         ###   ########.fr       */
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
	int		is_asgn;
	char	*seg;
	t_token	*new;

	is_asgn = 0;
	if (*i > 0 && input[*i - 1] == '=')
		is_asgn = 1;
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
		new->is_assign = is_asgn;
		return (new);
	}
	free(seg);
	return (NULL);
}
