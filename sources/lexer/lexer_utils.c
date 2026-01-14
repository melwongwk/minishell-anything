/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 06:57:08 by melwong           #+#    #+#             */
/*   Updated: 2026/01/14 13:01:00 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char c)
{
	return (c == '<' || c == '>');
}

void	handle_redirection(t_token **tokens, char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		token_append(tokens, token_new("<<", HEREDOC, DEFAULT));
		*i += 2;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		token_append(tokens, token_new(">>", APPEND, DEFAULT));
		*i += 2;
	}
	else if (input[*i] == '<')
	{
		token_append(tokens, token_new("<", INPUT, DEFAULT));
		(*i)++;
	}
	else if (input[*i] == '>')
	{
		token_append(tokens, token_new(">", TRUNC, DEFAULT));
		(*i)++;
	}
}

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*extract_var(char *s, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_strndup(s + start, *i - start));
	}
	while (s[*i] && is_var_char(s[*i]))
		(*i)++;
	return (ft_strndup(s + start, *i - start));
}
